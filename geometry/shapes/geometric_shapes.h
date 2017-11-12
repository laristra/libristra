/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief A geometric shapes enum class.
////////////////////////////////////////////////////////////////////////////////
#pragma once


namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

//////////////////////////////////////////////////////////////////////////////
//! An enum to identify the different geometric shapes
//////////////////////////////////////////////////////////////////////////////
enum class geometric_shapes_t 
{
  triangle,
  quadrilateral,
  polygon,
  tetrahedron,
  hexahedron,
  polyhedron
};


} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
