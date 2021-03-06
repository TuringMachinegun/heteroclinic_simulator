#include "lifnetsim.h"
#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include <boost/lexical_cast.hpp>

namespace po = boost::program_options;

struct Limit_parameter
{
  std::string limit_type;
  unsigned long int limit_n;
};

void validate(boost::any& v, const std::vector<std::string>& values,
	      Limit_parameter*, int)
{
    Limit_parameter limit;
    // Extract tokens from values string vector and populate Model struct.
    if (values.size() < 2)
    {
      std::cout << values.size() <<std::endl;
      std::cout << "Please specify limit\n";
      throw 1;
    }
    limit.limit_type = values.at(0);
    limit.limit_n = boost::lexical_cast<unsigned long>(values.at(1));

    v = limit;
}

int main(int argc, char *argv[]){

  std::vector<double> default_pulses({1.596, 1.596, 0.358, 0.358, 1.954});
  std::vector<double> default_volts({0, 0, 0.74039804, 0.74039804, 0.96216636});
  
  std::vector<double> deltas, pulses, volts;
  double noise_rate;
  double noise_amplitude_squared;
  std::string limit_run;
  unsigned long limit;

  Limit_parameter limit_param;
  
  std::string o_file_name;
  try{
    po::options_description desc("Options");
    desc.add_options()
      ("help,h", "produce help message")
      ("deltas,d", po::value< std::vector<double> >(&deltas)->multitoken()->required(),
       "list of delta currents")
      ("rate,r", po::value< double >(&noise_rate)->required(),
       "Noise rate")
      ("amp,a", po::value< double >(&noise_amplitude_squared)->required(), "Square root of noise amplitude")
      ("limit,l", po::value< Limit_parameter >(&limit_param)->multitoken()->required(),
       "Limit simulation run.\nSample usages:"
       "\nresets 1026 or"
       "\ntime 120 or"
       "\nsaddles 143.")
      ("out,o", po::value< std::string>(&o_file_name), "output file name")
      ("pulses,p", po::value< std::vector<double> >()->multitoken(),"initial pulse timings")
      ("volts,v", po::value< std::vector<double> >()->multitoken(), "initial volts")
      ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
  
    if (vm.count("help")){
      std::cout << desc << std::endl;
      return 1;
    }

    if (!vm.count("pulses")) pulses = default_pulses;
    else pulses = vm["pulses"].as< std::vector<double> >();

    if (!vm.count("volts")) volts = default_volts;
    else volts = vm["volts"].as< std::vector<double> >();

    po::notify(vm);
  }

  catch(std::exception& e){
    std::cerr << "Error: " << e.what() << "\n";
    return false;
  }
  catch(...){
    std::cerr << "Unknown error!" << "\n";
    return false;
  }

  //GOOGLE_PROTOBUF_VERIFY_VERSION;

  LifNetSim nuovo(volts, pulses, deltas, noise_rate, noise_amplitude_squared);
  
  try{
    std::ofstream ofs(o_file_name);
    nuovo.run(limit_param.limit_type, limit_param.limit_n);
    std::cout << nuovo.time << std::endl;
  
    nuovo.data_to_save.SerializeToOstream(&ofs);

    return 0;
  }
  catch(int e){

    std::string err_file_name = o_file_name + "_partial_";
    std::ofstream err_ofs(err_file_name);
    
    std::cerr << "Something bad happened.\n"
	      << "Partial results saved in "
	      << err_file_name
	      << std::endl;

    nuovo.data_to_save.SerializeToOstream(&err_ofs);    
    return -1;
    
  }
}

 
