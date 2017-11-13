/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utility functions for quadrilaterals.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/geometry/shapes/geometric_shapes.h"
#include "flecsi-sp/geometry/shapes/polygon.h"

namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

////////////////////////////////////////////////////////////////////////////////
//! \brief the quadrilateral class
//! \tparam N the number of dimensions
//! \remark This is the primary template
////////////////////////////////////////////////////////////////////////////////
template<std::size_t N>
struct quadrilateral {};

////////////////////////////////////////////////////////////////////////////////
//! \brief the quadrilateral class
//! \remark this is the 2D specialization
////////////////////////////////////////////////////////////////////////////////
template<>
struct quadrilateral<2> {

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::quadrilateral;

  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename... Args >
  static auto centroid( Args&&... pts ) 
  {
    return polygon<2>::centroid( std::forward<Args>(pts)... );
  }

  //============================================================================
  //! \brief the midpoint function
  //============================================================================
  template< typename T >
  static T midpoint( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3 
  ) {
    using value_type = typename T::value_type;
    constexpr auto fourth = 
      static_cast<value_type>(1) / static_cast<value_type>(4);
    return { 
      fourth * ( pt0[0] + pt1[0] + pt2[0] + pt3[  0] ),  
      fourth * ( pt0[1] + pt1[1] + pt2[1] + pt3 [1] ),  
    };
  }
  
  //============================================================================
  //! \brief the volume function
  //============================================================================
  template< typename... Args >
  static auto area( Args&&... pts ) 
  { 
    return polygon<2>::area( std::forward<Args>(pts)... );
  }

  
  //============================================================================
  //! \brief the normal of the quad
  //============================================================================
  template< typename... Args >
  static auto normal( Args&&... pts ) 
  { 
    return polygon<2>::normal( std::forward<Args>(pts)... );
  }

#if 0
  
  //============================================================================
  //! \brief the normal of the quad
  //============================================================================
  template< typename T >
  static auto normal( const T & pt0, const T & pt1, const T & pt2, const T & pt3 ) 
  { 
    auto n = triangle<3>::normal( pt0, pt1, pt2 );
    n += triangle<3>::normal( pt2, pt3, pt0 );
    return n;
  }

#endif
    
};



////////////////////////////////////////////////////////////////////////////////
//! the quadrilateral class
//! \remark this is the 2D specialization
////////////////////////////////////////////////////////////////////////////////
template<>
struct quadrilateral<3> {

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::quadrilateral;

  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename... Args >
  static auto centroid( Args&&... pts ) 
  {
    return polygon<3>::centroid( std::forward<Args>(pts)... );
  }


  //============================================================================
  //! \brief the midpoint function
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
  //! \brief the centroid function
  //============================================================================
  template< typename... Args >
  static auto area( Args&&... pts ) 
  {
    return polygon<3>::area( std::forward<Args>(pts)... );
  }

  //============================================================================
  //! \brief the normal of the quad
  //============================================================================
  template< typename... Args >
  static auto normal( Args&&... pts ) 
  {
    return polygon<3>::normal( std::forward<Args>(pts)... );
  }
  

#if 0

  //============================================================================
  //! \brief the volume function
  //============================================================================
  template< typename T >
  static auto area( const T & pt0, const T & pt1, const T & pt2, const T & pt3 ) 
  { 
    auto xc = centroid( pt0, pt1, pt2, pt3 );
    auto a = 
      triangle<3>::area( pt0, pt1, xc ) + 
      triangle<3>::area( pt1, pt2, xc ) + 
      triangle<3>::area( pt2, pt3, xc ) +
      triangle<3>::area( pt3, pt0, xc );
    return a;
  }

  
  //============================================================================
  //! \brief the normal of the quad
  //============================================================================
  template< typename T >
  static auto normal( const T & pt0, const T & pt1, const T & pt2, const T & pt3 ) 
  { 
    auto xc = centroid( pt0, pt1, pt2, pt3 );
    auto n = triangle<3>::normal( pt0, pt1, xc );
    n += triangle<3>::normal( pt1, pt2, xc );
    n += triangle<3>::normal( pt2, pt3, xc );
    n += triangle<3>::normal( pt3, pt0, xc );
    return n;
  }

#endif
    
};

} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
