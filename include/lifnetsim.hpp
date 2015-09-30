#include <random>
#include <vector>
#include <string>
#include <deque>
#include <boost/serialization/vector.hpp>
#include <fstream>
#include "sim_data_transf.pb.h"

//! Return intrinsic period of oscillator
double tif(double gamma=1.0, double current=1.04, double tau=1.0);

//! Return new voltage given starting voltage, current and time passed
double v_after_t(double start_voltage=0, double time_interval=0,
		 double current=1.04);

//! Convert voltage to phase
double v_to_ph(double voltage, double tif, double gamma=1.0,
	       double current=1.04,
	       double tau=1.0);

//! Return time to reach a given voltage given starting voltage and current.
/*!
  \param start starting voltage
  \param stop voltage to reach
  \param current input current
 */
double t_to_reach_v(double start=0.0, double stop=1.0, 
		    double current=1.04);

//! Class implementing the network event based simulator
/*!
  more stuff
 */
class LifNetSim {

  friend class boost::serialization::access;

  std::random_device rd;
  /* mersenne twister algorithm*/
  std::mt19937 gen = std::mt19937(rd());
  /*! a coin tosser*/
  std::bernoulli_distribution ctoss = std::bernoulli_distribution(0.5);
  /*! used to generate noise pulses */
  std::exponential_distribution<> exp_dist;

  char *saddle;

public:

  data_transf::Data_dump data_to_save;
  /*! Dump data in file every save_interval saddles*/
  const int save_interval = 50;
  /*! Each Oscillator variable contains reset timings for one oscillator*/
  std::vector<data_transf::Oscillator *> osc_to_save;
  
  unsigned int n_osc; /*!< Number of oscillators in network*/
  std::vector<double> osc_volts; /*!< Voltages of oscillators*/
  //! network pulses timings for each oscillaor
  std::vector<std::deque<double> > net_pulses;
  //! pulses from the outside to be applied to each oscillator (noise)
  std::vector<double > ext_pulses;
  std::vector<double> deltas; /*!< Delta currents for each oscillator*/
  
  const double I = 1.04; /*!< Input current */
  const double gamma = 1; /*!< Membrane constant */
  const double tau = 1; 
  const double net_psp = 0.025; /*!< Post-synaptic potential of pulse */
  const double pdelay = 0.49; /*!< Phase delay of pulses */
  const double tdelay = pdelay * tif(gamma, I, tau); /*!< Time delay of pulses*/
  double ext_psp = 0; /*!< Post-synaptic potential of external pulses (noise)*/
  double noise_rate = 0;

  bool *who_received;
  bool *who_reset;

  /*!
    DFA to check saddle is reached
    states in rows, symbols in columns
    symbols is the number of oscillators resetting due to a pulse.
    If DFA reaches state 4, then a new saddle is reached.
    
    +-----+-----+-----+-----+
    |     |  0  |  1  |  2  |
    +-----+-----+-----+-----+
    |  0  |  0  |  1  |  0  |
    +-----+-----+-----+-----+
    |  1  |  0  |  0  |  2  |
    +-----+-----+-----+-----+
    |  2  |  3  |  0  |  0  |
    +-----+-----+-----+-----+
    |  3  |  0  |  0  |  4  |
    +-----+-----+-----+-----+
    |  4  |  0  |  0  |  0  |
    +-----+-----+-----+-----+

    The DFA reflects the sequence:
    - singleton resets because of a pulse
    - stable cluster resets because of pulse
    - the new singleton resets naturally
    - the new stable cluster resets because of pulse (new saddle reached, accept)

    The symbols in the DFA mean:
    0: one or more natural resets were observed
    1: a single reset because of pulses was observed
    2: two resets because of pulses were observed

    note that the ambiguity of 0 is not important, as the table of events 
    (In Fabio's thesis) assures that at DFA state 2, the only natural reset 
    that can be observed is that of the new singleton.
    So when the symbol 0 is received in state 2, it can only signify that
    the new singleton fired.

    The DFA transition table is implemented in a bidimensional array:
  */
  int s_DFA[5][3] =
    {
      {0, 1, 0},
      {0, 0, 2},
      {3, 0, 0},
      {0, 0, 4},
      {0, 0, 0}
    };
  
  int s_DFA_curr_state = 0;
  int s_DFA_accept = 4; /*!< accept state of DFA*/

  //! Network connection matrix
  std::vector<std::vector<double> > net_conn_mat;

  double t_to_next_event = double(INFINITY);

  unsigned long time_units = 0;
  double time_subunits = 0;
  double time = 0; /*!< keeps simulation time*/
  bool stop_run = false; /*!< When true, simulation loop breaks*/
  bool record = false; /*!< When true, the data from the simulation is saved*/

  /*! std::vector storing data on event_timings*/
  std::vector<double > timings;
  std::vector<std::vector<double> > phases; /*!< phases for each timing*/

  /*! a counter for the number of resets during the simulation */
  unsigned long reset_counter = 0;
  unsigned long saddle_counter = 0;

  

  //! Runs the simulation given a trial_time or n_resets (not both, error is given).
  /*!
    \param trial_time the total time of the simulation
    \param n_resets the total number of resets for the reference neuron until
    the simulation is stopped.
    \param record set to true if you want the simulation data saved
   */
  
  void run(std::string limit_run, long unsigned limit);

  //! Finds the nearest reset from the oscillators
  void nearest_reset_t(std::vector<int>&, double&);

  //! Adds incoming pulses from network neurons
  void receive_net_pulses(bool *who_received);

  void update_net_pulses_timings();

  double generate_ext_pulse_t();

  //! Adds incoming pulses from the outside
  void receive_ext_pulses();

  void update_ext_pulses_timings();

  void save_saddle_t_and_id();

  void save_reset_timing(int osc);

  void check_saddle();

  //! 1 -> 0 and send pulses from resetting oscillators, returns array of bool
  void check_resets(bool *who_reset);

  //! Create new simulation
  LifNetSim(std::vector<double> volts, std::vector<double> pulses,
	    std::vector<double> deltas, double noise_rate=0,
	    double ext_psp=0);
  ~LifNetSim();
};
