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
  //! Mersenne twister algorithm
  std::mt19937 gen = std::mt19937(rd());
  //! Coin tosser
  std::bernoulli_distribution ctoss = std::bernoulli_distribution(0.5);
  //! Used to generate noise pulses
  std::exponential_distribution<> exp_dist;

public:

  //! Google protobuf data container
  data_transf::Data_dump data_to_save;
  //! Each Oscillator variable contains reset timings for one oscillator
  std::vector<data_transf::Oscillator *> osc_to_save;

  //! Number of oscillators in network
  unsigned int n_osc;
  //! Voltages of oscillators
  std::vector<double> osc_volts;
  //! Network pulses timings for each oscillaor
  std::vector<std::deque<double> > net_pulses;
  //! Pulses from the outside to be applied to each oscillator (noise)
  std::vector<double > ext_pulses;
  //! Delta current for each oscillator
  std::vector<double> deltas;

  //! Input current 
  const double I = 1.04;
  //! Dissipative factor 
  const double gamma = 1;
  //! Membrane constant 
  const double tau = 1;
  //! Post-synaptic potential of pulse 
  const double net_psp = 0.025;
  //! Phase delay of pulses 
  const double pdelay = 0.49;
  //! Time delay of pulses
  const double tdelay = pdelay * tif(gamma, I, tau);
  //! Post-synaptic potential of external pulses (noise)
  double ext_psp = 0;
  //! Rate of noise 
  double noise_rate = 0;

  // TODO These guys should probably not be here.  They don't need to be in
  // the class, as they are used only during the run, and reset at
  // each iteration.
  bool *who_received;
  bool *who_reset;
  char *saddle;

  /*!
    DFA to check saddle is reached
    states in rows, symbols in columns
    symbols is the number of oscillators resetting due to a pulse.
    If DFA reaches state 4, then a new saddle is reached.
   
    \verbatim
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
    \endverbatim

    The DFA reflects the sequence:
    - singleton resets because of a pulse
    - stable cluster resets because of pulse
    - the new singleton resets naturally
    - the new stable cluster resets because of pulse (new saddle reached, accept)

    The symbols in the DFA mean:
    0: one or more natural resets were observed
    1: a single reset because of pulses was observed
    2: two resets because of pulses were observed

    note that the ambiguity of 0 is not important, as the table of
    events (see Schittler Neves, Fabio: Universal Computation and
    Memory by Neural Switching, 2010 ) assures that at DFA state 2,
    the only natural reset that can be observed is that of the new
    singleton. So when the symbol 0 is received in state 2, it can
    only signify that the new singleton fired.

    The DFA transition table is implemented in a bidimensional array.
  */
  int s_DFA[5][3] =
    {
      {0, 1, 0},
      {0, 0, 2},
      {3, 0, 0},
      {0, 0, 4},
      {0, 0, 0}
    };
  
  //! current state of DFA
  int s_DFA_curr_state = 0;
  //! accept state of DFA
  int s_DFA_accept = 4;

  //! Network connection matrix
  std::vector<std::vector<double> > net_conn_mat;

  //! Time to next event
  double t_to_next_event = double(INFINITY);

  //! Time units elapsed since run start
  unsigned long time_units = 0;
  //! Time subunits since last time unit
  double time_subunits = 0;
  //! Simulation time since run start
  double time = 0;
  //! When true, simulation loop breaks
  bool stop_run = false;

  //! A counter for the number of resets of reference oscillator since
  //! run start
  unsigned long reset_counter = 0;
  //! A counter for the number of saddle reached since run start
  unsigned long saddle_counter = 0;

  //! Used in initialization and when resetting of initial condition
  //! is needed
  void set_init_cond(std::vector<double> init_volts,
		     std::vector<double> pulses,
		     std::vector<double> init_deltas);

  //! Runs the simulation given a trial_time or n_resets (not both, error is given).
  /*!
    \param trial_time the total time of the simulation
    \param n_resets the total number of resets for the reference neuron until
    the simulation is stopped.
   */
  void run(std::string limit_run, long unsigned limit);

  //! Finds the nearest reset time from the oscillators
  void nearest_reset_t(std::vector<int>&, double&);

  //! Adds incoming pulses from network neurons
  void receive_net_pulses(bool *who_received);

  //! Updates timings of pulses from network
  void update_net_pulses_timings();

  //! Randomly generates new noise pulses
  double generate_ext_pulse_t();

  //! Adds incoming pulses from the outside
  void receive_ext_pulses();

  //! Updates timings of pulses outside network (noise)
  void update_ext_pulses_timings();

  //! Saves saddle and its timing for later dumping to file via
  //! function save_data
  void save_saddle_t_and_id();

  //! Save timing of oscillator osc, for later dumping to file via
  //! function save_data
  void save_reset_timing(int osc);

  //! Save simulation data to file
  void save_data(std::string file_name);

  //! Updates saddle DFA and checks if saddle has been reached
  void check_saddle();

  //! Used in initialization and when setting noise parameters is
  //! needed
  void set_noise(double noise_rate, double noise_amplitude_squared);
  
  //! 1 -> 0 and send pulses from resetting oscillators,
  // \param who_reset is modified to reflect the resetting oscillators
  void check_resets(bool *who_reset);

  //! Create new simulator
  LifNetSim(std::vector<double> volts, std::vector<double> pulses,
	    std::vector<double> deltas, double noise_rate=0,
	    double ext_psp=0);
  ~LifNetSim();}
;
