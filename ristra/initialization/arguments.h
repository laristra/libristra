/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Utilities to process command line arguments.
///////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include <boost/program_options.hpp>

// system includes
#include<iostream>

namespace ristra {
namespace initialization {
  
class command_line_variables_t {

  boost::program_options::variables_map variables_;

public:
  command_line_variables_t(
      const boost::program_options::variables_map & variables) :
    variables_(variables)
  {}

  template<typename T>
  auto as(const std::string & var_name, const T & def = T() ) const
  {
    if ( variables_.count(var_name) )
      return variables_[var_name].as<T>();
    else
      return def;
  }
  
  auto count(const std::string & var_name) const
  {
    return variables_.count(var_name);
  }

};

///////////////////////////////////////////////////////////////////////////////
//! \brief A class to register the arguements
///////////////////////////////////////////////////////////////////////////////
class command_line_arguments_t {

  //! store the options
  std::map<std::string, boost::program_options::options_description> descriptions_;
  
  //! keep track of the program name
  std::string program_name_;

  //! a struct for returning parsed arguments
  struct arguments_return_t {
    command_line_variables_t variables;
    bool error = false;
  };

public:
  
  static command_line_arguments_t& instance()
  {
    static command_line_arguments_t s;
    return s;
  };

  
  //===========================================================================
  //! register an argument group
  //===========================================================================
  bool register_group( std::string key, std::string title ) {

    // try to add it
    auto res = descriptions_.emplace(key, title.c_str());
    return true;

  }
  //===========================================================================
  //! register the arguments
  //===========================================================================
  bool register_argument(
    std::string key,
    std::string flag,
    std::string message
  ) {

    // try to add it
    auto & desc = descriptions_[key];

    // add the arguments
    desc.add_options()(flag.c_str(), message.c_str());

    return true;
  }


  template<typename T>
  bool register_argument(
    std::string key,
    std::string flag,
    std::string message
  ) {

    // try to add it
    auto & desc = descriptions_[key];

    // add the arguments
    namespace po = boost::program_options;
    desc.add_options()(flag.c_str(), po::value<T>(), message.c_str());

    return true;
  }

  //===========================================================================
  //! \brief Process the argument list for this app.
  //===========================================================================
  arguments_return_t process_arguments(int argc, char** argv, bool print=true) 
  {

    namespace po = boost::program_options;

    program_name_ = argv[0];

    po::options_description cmdline_options;
    for ( auto desc : descriptions_ ) {
      cmdline_options.add(desc.second);
    }

    po::variables_map vm;
    
    try
    {
      po::command_line_parser parser{argc, argv};
      auto parsed = parser.options(cmdline_options).allow_unregistered().run();
      auto to_pass_further = po::collect_unrecognized(parsed.options, po::include_positional);
      po::store(parsed, vm);
      po::notify(vm); 
    
    }
    catch(po::error& e)
    {
      if (print) {
        std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
        std::cerr << "Usage: " << argv[0] << " [options]\n";
        std::cerr << cmdline_options << "\n";
      }
      return { vm, true };
    }

    if (vm.count("help") && print) {
      std::cout << "Usage: " << argv[0] << " [options]\n";
      std::cout << cmdline_options << "\n";
    }

    return { vm, false };
  }
      
  auto print_missing_argument(const std::string & arg_name)
  {
    
    namespace po = boost::program_options;
    po::options_description cmdline_options;
    for ( auto desc : descriptions_ ) {
      cmdline_options.add(desc.second);
    }

    std::stringstream ss;
    ss << "ERROR: Missing command line argument '" << arg_name << "'";
    ss << std::endl << std::endl;
    ss << "Usage: " << program_name_ << " [options]\n";
    ss << cmdline_options << "\n";

    return ss.str();
  }

}; // class


} // namespace
} // namespace
