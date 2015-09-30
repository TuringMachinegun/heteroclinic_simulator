#include "lifnetsim.hpp"

#include <math.h>
#include <limits>
#include <algorithm>
#include <iostream>

#define foreach_ BOOST_FOREACH
#define DEBUG false


double tif(double gamma, double current, double tau){
  return -(tau / gamma) * log(-1/current +1 );
}


double v_after_t(double start_voltage, double time_interval,
		 double current){

  return current*( 1 - exp(-time_interval)) + start_voltage *
		   exp(-time_interval);
}

double v_to_ph(double voltage, double tif, double gamma,
	       double current,
	       double tau){
  voltage = voltage < 0 ? 0 : voltage > 1 ? 1 : voltage;
  return (-(tau/gamma)/tif) * log(voltage * (-gamma/current) + 1);
}

double t_to_reach_v(double start, double stop, 
		    double current){
  return -log((current-stop)/(current-start));
}

void LifNetSim::nearest_reset_t(std::vector<int> &osc_minres_idxs,
				double &min_reset_t){
  int i_max = -1;
  double max_volt = -1;

  for(int i=0; i < this->n_osc; i++)
    if (this->osc_volts[i] > max_volt){
      i_max = i;
      max_volt = osc_volts[i];
    }
  
  for (int i=0; i < this->n_osc; i++) 
    if (this->osc_volts[i] == max_volt)
      osc_minres_idxs.push_back(i);

  double time_to_reset = t_to_reach_v(this->osc_volts[i_max],
				      1.0,
				      this->I + this->deltas[i_max]);

  min_reset_t = time_to_reset;

}

void LifNetSim::receive_net_pulses(bool *who_received){
  for(int i=0; i < this->n_osc; i++){
    if ((this->net_pulses[i].size() != 0) &&
	(this->net_pulses[i].back() == 0)){
      for(int j=0; j < this->n_osc; j++)
	{
	this->osc_volts[j] += this->net_conn_mat[i][j];
	if(this->net_conn_mat[i][j] != 0) who_received[j] = true;
	}
      
      this->net_pulses[i].pop_back();
    }
  }
}

void LifNetSim::update_net_pulses_timings(){
  for(int i=0; i < this->n_osc; i++){
    int deque_size = this->net_pulses[i].size();
    if(deque_size>0)
      for(int j = 0; j<deque_size; j++){
        net_pulses[i][j] -= this->t_to_next_event;
      }
  }
}

double LifNetSim::generate_ext_pulse_t(){
  return this->exp_dist(this->gen);
}

void LifNetSim::receive_ext_pulses(){
  double pos_neg[] = {-1, 1};
  for(int i=0; i < this->n_osc; i++){
    if (this->ext_pulses[i] == 0){
      int coin = this->ctoss(this->gen);
      this->osc_volts[i] += this->ext_psp * pos_neg[coin];
      this->ext_pulses[i] = this->generate_ext_pulse_t();
    }
  }
}

void LifNetSim::update_ext_pulses_timings(){
  for(int i=0; i < this->n_osc; i++){
    this->ext_pulses[i] -= this->t_to_next_event;
  }
}

void LifNetSim::save_reset_timing(int osc){
  this->osc_to_save[osc]->add_reset_t(this->time);
}

void LifNetSim::save_saddle_t_and_id()
{
  data_transf::Saddle_t_and_id * saddle_t_id = this->data_to_save.add_saddle_t_and_id();
  saddle_t_id->set_saddle_id(this->saddle, this->n_osc);
  saddle_t_id->set_saddle_t(this->time);
}


void LifNetSim::check_resets(bool *who_reset){

  for (int i=0; i < this->n_osc; i++)
    if (this->osc_volts[i] >= 1){
      who_reset[i] = true;
      this->osc_volts[i] = 0;
      this->net_pulses[i].push_front(this->tdelay);
      save_reset_timing(i);
    }
}

void LifNetSim::check_saddle()
{  
  int resetting_for_pulse = 0; /*!< number of oscs resetting because pulse*/
  int resetting_naturally = 0; /*!< number of oscs resetting with no pulse*/
  
  for (int i = 0; i<this->n_osc; i++){
    resetting_for_pulse += this->who_reset[i] && this->who_received[i];
    resetting_naturally += this->who_reset[i] && !this->who_received[i];
  }

  if (resetting_for_pulse  <= 2
      &&
      (resetting_naturally + resetting_for_pulse > 0)){
      
    this->s_DFA_curr_state = s_DFA[s_DFA_curr_state][resetting_for_pulse];

    char cluster = 'x';
      
    switch (s_DFA_curr_state)
      {
	  
      case 2: cluster = 'a';
	break;
	  
      case 3: cluster = 'c';
	break;

      case 4: cluster = 'b';
	break;
      }

    for(int i=0; i<this->n_osc; i++)
      if(who_reset[i])
	this->saddle[i] = cluster;

    if(this->s_DFA_curr_state == this->s_DFA_accept)
      {	
      this->save_saddle_t_and_id();
      this->saddle_counter++;
      }
    
  }
  
  else if(resetting_for_pulse > 2 || resetting_naturally > 2){
    std::cerr << "Too many oscs resetting for pulse, dynamics broken";
    this->stop_run = true; // useless
    throw 1;
  }  

} // check_saddle


LifNetSim::LifNetSim(std::vector<double> init_volts,
		     std::vector<double> pulses,
		     std::vector<double> init_deltas,
		     double noise_rate,
		     double noise_amplitude_squared
		     ){  
  this->osc_volts = init_volts;
  this->deltas = init_deltas;
  /*!< this->noise_rate is just the rate for one of the two generators
     (positive and negative), so that the passed argument has to be
     multiplied by two */
  this->noise_rate = 2*noise_rate;
  this->ext_psp = sqrt(noise_amplitude_squared);
  
  this->exp_dist = std::exponential_distribution<>(this->noise_rate);

  this->n_osc = init_volts.size();
  this->net_pulses.resize(this->n_osc);
  this->ext_pulses.assign(this->n_osc, double(INFINITY));

  this->net_conn_mat.resize(n_osc);

  this->saddle = new char[this->n_osc];
  this->who_reset = new bool[this->n_osc];
  this->who_received = new bool[this->n_osc];
  
  for(int i = 0; i<this->n_osc; i++){
    
    this->net_pulses[i].push_back(pulses[i]);

    this->ext_pulses[i] = this->exp_dist(gen); /*!< generate first ext pulses*/
    
    this->net_conn_mat[i].resize(n_osc, this->net_psp);
    this->net_conn_mat[i][i] = 0;

    this->osc_to_save.push_back(this->data_to_save.add_oscillator());
  }

  // shrinking is gross overkilling, but few lines of code called just once...
  this->osc_volts.shrink_to_fit();
  this->deltas.shrink_to_fit();
  this->net_pulses.shrink_to_fit();
  this->ext_pulses.shrink_to_fit();
  this->net_conn_mat.shrink_to_fit();
}


void LifNetSim::run(std::string run_limit, unsigned long limit){
  this->stop_run = false;
  this->reset_counter = 0;
  this->time = 0;
  this->saddle_counter = 0;

  /*! 
    This variable is here to make sure that neither one of time_units, 
    reset_counter or saddle_counter overflows. If one of them reaches
    absolute_limit, the simulation stops.
    Special care is given to time though, as it doesn't increment in units.
  */
  unsigned long absolute_limit = std::numeric_limits<unsigned long>::max();
  unsigned long resets_limit = absolute_limit;
  unsigned long time_limit = absolute_limit;
  unsigned long saddles_limit = absolute_limit;

  unsigned long *counterp, *limitp;
  int print_every_n_units = 100;
  unsigned long old_counter = 0;

  unsigned long old_saddle_count = this->saddle_counter;
  unsigned int resets_since_last_saddle = 0;

  if(run_limit=="resets"){
    resets_limit = limit;
    limitp = &resets_limit;
    counterp = &this->reset_counter;
  }
  else if (run_limit=="time"){
    time_limit = limit;
    limitp = &time_limit;
    counterp = &this->time_units;
  }
  else if (run_limit=="saddles"){
    saddles_limit = limit;
    limitp = &saddles_limit;
    counterp = &this->saddle_counter;
  }
  
  else{
    std::cerr << "Error: bad argument. Specify one between \"resets\", "
	      << "\"time\" or \"saddles\".";
    throw 1;
  }
    
  while(!this->stop_run){
    // ------ collect nearest events: --------

    // nearest pulse from network
    double min_net_pulse_t = double(INFINITY);
    for(int i=0; i < this->n_osc; i++){
      if (this->net_pulses[i].size()>0){
	double net_pulse_t = this->net_pulses[i].back();
	if (net_pulse_t < min_net_pulse_t)
	  min_net_pulse_t = net_pulse_t;
      }
    }

    // nearest pulse from the outside
    double min_ext_pulse_t = double(INFINITY);
    for(int i = 0; i < this->n_osc; i++){
      if (this->ext_pulses[i]< min_ext_pulse_t)
	min_ext_pulse_t = ext_pulses[i]; 
    }

    // nearest reset
    std::vector<int> osc_minres_idxs;
    double min_reset_t;
    this->nearest_reset_t(osc_minres_idxs, min_reset_t);

    /*
     * nearest pulse from network, from the outside and nearest reset are
     * now known. 
     */
    
    // find nearest event
    double min_events[3] = {min_net_pulse_t, min_ext_pulse_t, min_reset_t};

    this->t_to_next_event = double(INFINITY);
    for(int i=0; i<3; i++){
      if (min_events[i] < this->t_to_next_event)
	this->t_to_next_event = min_events[i];
    }

    /*
     * Calculate next time
     */
    this->time_subunits += this->t_to_next_event; 
    if (this-> time_subunits >=1){
      this->time_units += (unsigned long) time_subunits; //floor and add
      this->time_subunits = fmod(this->time_subunits, 1); // modulus 1
    }
    this->time = (double) this->time_units + this->time_subunits;

    
    /*
     * Now we can jump to next event:
     * - update voltages,
     * - update times to next pulses from network
     *     in particular, these timings are all relative to the current time,
     *     so each timing in each queue has to be corrected
     * - update times to next pulses from outside
     *     these instead don't need to be. In current implementation, each time
     *     a spike is received from a unit, another timing is generated with a
     *     Poisson distribution.
     * - receive pulses if it's time to receive them.
     * - check if some oscillator voltage is >=1. In this case, reset and add
     *     a pulse to the queues for the other oscillators
     */

    //update voltages
    for (int i=0; i < this->osc_volts.size(); i++)
      this->osc_volts[i] = v_after_t(this->osc_volts[i], this->t_to_next_event,
				     this->I + this->deltas[i]);
    
    /* 
     * Make sure resetting units are exactly at 1 
     * (counteract num errors introduced by passage between log and exp)
     */
    if (min_reset_t==this->t_to_next_event)
      for(int idx : osc_minres_idxs)
	this->osc_volts[idx] = 1;
        
    this->update_net_pulses_timings();
    this->update_ext_pulses_timings();

    /*! reset who_received to initial state, ready to be updated */
    for(int i = 0; i<this->n_osc; i++) this->who_received[i] = false;
    /*!
      If osc i received a pulse, add that to osc i voltage,
      and set who_received[i] == true.
    */
    this->receive_net_pulses(this->who_received);
    this->receive_ext_pulses();

    /*! reset who_reset to initial state, ready to be updated */
    for(int i = 0; i<this->n_osc; i++) this->who_reset[i] = false;
    /*! Reset oscillator i if voltage >= 1, and set who_reset[i]=true. */
    this->check_resets(this->who_reset);

    /*
      check if new saddle is reached deciding by using the s_DFA.
      If updating the state of the s_DFA yields an accept state, 
      save new saddle as a char array where each character i is either

      a - if osc i in unstable cluster
      b - if osc i in stable cluster
      c - if osc i is singleton
    */
    
    this->check_saddle();

    if (this->osc_volts[0]==0) this->reset_counter++;

    if(*counterp % print_every_n_units == 0 && *counterp != old_counter){
      std::cout << *counterp << " over " << *limitp << std::endl;
      old_counter = *counterp;
    }

    if(this->saddle_counter > old_saddle_count){
      old_saddle_count = this->saddle_counter;
      resets_since_last_saddle = 0;
    }
    else if(this->osc_volts[0]==0) resets_since_last_saddle++;

    if(resets_since_last_saddle > 200){
      std::cerr << "Dynamics most likely broken. Exiting." << std::endl;
      throw 1;
    }

      
    /*! time's out! */
    if (this->reset_counter > resets_limit ||
	this->time_units > time_limit ||
	this->saddle_counter > saddles_limit)
      this->stop_run = true;
  }
}

LifNetSim::~LifNetSim(){
  delete[] saddle;
  delete[] who_reset;
  delete[] who_received;
}
