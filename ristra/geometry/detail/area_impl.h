/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Evaluate the area of geometric entities.
////////////////////////////////////////////////////////////////////////////////
#pragma once

namespace ristra {
namespace geometry {
namespace detail {




////////////////////////////////////////////////////////////////////////////////
// Template helper to compute areas
////////////////////////////////////////////////////////////////////////////////

//! \brief area operator.
template< class U, class V >
constexpr void area_2d( U & vol, V && v )
{ 
  // nothing left to do
}

//! \brief average operator.
template< class U, class V1, class V2, class ... Args >
constexpr void area_2d( U & vol, V1 && v1, V2 && v2, Args&&... args )
{ 
  
  vol += v1[0]*v2[1] - v2[0]*v1[1];
  area_2d( vol, 
           std::forward<V2>(v2), 
           std::forward<Args>(args)... ); 
}


} // namespace
} // namespace
} // namespace
