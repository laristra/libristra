// type_utils.h
// Aug 30, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include <cxxabi.h> // works for clang 3.9.0, reported ok for GCC

namespace ristra
{
namespace detail
{
/**\brief Use non-standard approach to demangle the type_info name. */
template <class T>
std::string type_as_string()
{
  std::string tname = typeid(T).name();
  int stat;
  char * demangled_name = abi::__cxa_demangle(tname.c_str(), NULL, NULL, &stat);
  if (0 == stat) {
    tname = demangled_name;
    free(demangled_name);
  }
  return tname;
} // type_as_string
}
}
// End of file
