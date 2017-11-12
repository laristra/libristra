/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utility functions for tetrahedrons.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/geometry/shapes/geometric_shapes.h"
#include "flecsi-sp/math/general.h"

namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

////////////////////////////////////////////////////////////////////////////////
//! \brief the tetrahedron class
////////////////////////////////////////////////////////////////////////////////
struct tetrahedron {

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::tetrahedron;

  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename... Args >
  static auto centroid( Args&&... pts ) 
  {
    return midpoint( std::forward<Args>(pts)... );
  }


  //============================================================================
  //! \brief the midpoint is the same as the centroid
  //============================================================================
  template< typename T >
  static T midpoint( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3 
  ) {
    using value_type = typename T::value_type;
    constexpr auto fourth = 
      static_cast<value_type>(1) / static_cast<value_type>(4);
    return { 
      fourth * ( pt0[0] + pt1[0] + pt2[0] + pt3[0] ),  
      fourth * ( pt0[1] + pt1[1] + pt2[1] + pt3[1] ), 
      fourth * ( pt0[2] + pt1[2] + pt2[2] + pt3[2] ),      
    };
  }
  
  //============================================================================
  //! \brief the volume function
  //============================================================================
  template< typename T >
  static auto volume( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3 ) 
  {
    auto det = 
      pt0[0]*pt1[1]*pt2[2] + 
      pt0[1]*pt1[2]*pt3[0] + 
      pt0[2]*pt2[0]*pt3[1] + 
      pt1[0]*pt2[1]*pt3[2] -
      pt3[0]*pt2[1]*pt1[2] - 
      pt3[1]*pt2[2]*pt0[0] - 
      pt3[2]*pt1[0]*pt0[1] - 
      pt2[0]*pt1[1]*pt0[2];
    return std::abs(det) / 6;
  }
  
    


};

} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
