/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/

////////////////////////////////////////////////////////////////////////////////
///
/// \file
/// \brief Functions to write binary files in vtk format.
///
////////////////////////////////////////////////////////////////////////////////
// user includes
#include "ristra/io/vtk.h"

namespace ristra {
namespace io {


////////////////////////////////////////////////////////////////////////////////
// the type map
////////////////////////////////////////////////////////////////////////////////
const vtk_writer::type_map_t vtk_writer::type_map = 
  { 
    { typeid(float),  "float" },
    { typeid(double), "double" },
    { typeid(int),    "int" },
    { typeid(long),   "long" },
    { typeid(unsigned int),  "unsigned_int" },
    { typeid(unsigned long), "unsigned_long" },
  };

} // namespace io
} // namespace ristra
