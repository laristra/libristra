/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/

#pragma once
//!
//! \file
//!

//#include <iostream>
#include <cstdio>
#include <string>


#define RISTRA_HERE \
  __FILE__ << " :: " << __FUNCTION__ << " :: L" << __LINE__

// Macro: call here_func(), using standard values for most arguments
#define HERE(message) \
  ristra::assertions::here_func(__FILE__, __FUNCTION__, __LINE__, message)

#define HERE_STR(message) \
  ristra::assertions::here_str_func(__FILE__, __FUNCTION__, __LINE__, message)

namespace ristra {
namespace assertions {

// Print a diagnostic message, along with source code location
inline void here_func(char const * const filename, char const * const fname,
  int const line, std::string const & s)
{
  printf("HERE %s:%s:%d %s\n", fname, filename, line, s.c_str());
}

inline std::string here_str_func(char const * const filename,
  char const * const fname, int const line, std::string const & s)
{
  std::string str =
    filename + std::string(":") + fname + ":" + std::to_string(line) + " " + s;
  return str;
}
} // namespace assertions
} // namespace ristra

