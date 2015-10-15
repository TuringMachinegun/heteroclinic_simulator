%module lifnetsim

%feature("autodoc", "1");

%{
#include "lifnetsim.h"
%}

%include "std_string.i"
%include "std_vector.i"

namespace std{
	%template(DoubleVector) std::vector<double>;
}

class LifNetSim
{
public:
  void set_init_cond(std::vector<double> init_volts,
		     std::vector<double> pulses,
		     std::vector<double> init_deltas);
  
  void run(std::string limit_run, long unsigned limit);

  void save_data(std::string file_name);

  //! Create new simulation
  LifNetSim(std::vector<double> volts, std::vector<double> pulses,
	    std::vector<double> deltas, double noise_rate=0,
	    double ext_psp=0);
  ~LifNetSim();
};
