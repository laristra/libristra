/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Evaluate the centroid of a list of points.
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace ristra {
namespace geometry {
namespace detail {




////////////////////////////////////////////////////////////////////////////////
// Template helper to compute centroids
////////////////////////////////////////////////////////////////////////////////

//! \brief average operator.
template< class T, class U, class V >
constexpr void centroid_2d( T & cx, U & vol, V && v )
{ 
  // nothing left to do
}

//! \brief average operator.
template< class T, class U, class V1, class V2, class ... Args >
constexpr void centroid_2d( T & cx, U & vol, V1 && v1, V2 && v2, Args&&... args )
{ 
  
  auto tmp = v1[0]*v2[1] - v2[0]*v1[1];
  cx[0] += ( v1[0] + v2[0] ) * tmp;
  cx[1] += ( v1[1] + v2[1] ) * tmp;
  vol += tmp;
  centroid_2d( cx, 
               vol, 
               std::forward<V2>(v2), 
               std::forward<Args>(args)... ); 
}


} // namespace
} // namespace
} // namespace
