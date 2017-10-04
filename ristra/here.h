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

// Macro: call here_func(), using standard values for most arguments
#define HERE(message) \
  ristra::here_func(__FILE__, __FUNCTION__, __LINE__, message)

#define HERE_STR(message) \
  ristra::here_str_func(__FILE__, __FUNCTION__, __LINE__, message)

namespace ristra {

// Print a diagnostic message, along with source code location
inline
void here_func(
  char const * const filename,
  char const * const fname,
  int const line,
  std::string const & s
) {
  printf("HERE %s:%s:%d %s\n",fname,filename,line,s.c_str());
}

inline std::string here_str_func(
  char const * const filename,
  char const * const fname,
  int const line,
  std::string const & s
  )
  {
    std::string str = filename + std::string(":") + fname + ":" +
      std::to_string(line) + " " + s;
    return str;
  }
} // ristra::

/*~-------------------------------------------------------------------------~-*
 * Formatting options
 * vim: set tabstop=2 shiftwidth=2 expandtab :
 *~-------------------------------------------------------------------------~-*/
