/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file triangle.h
/// \brief Some utility functions for triangles.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "geometric_shapes.h"
#include "../../math/general.h"

namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

////////////////////////////////////////////////////////////////////////////////
//! \brief the triangle class
//! \tparam N the number of dimensions
//! \remark This is the primary template
////////////////////////////////////////////////////////////////////////////////
template<std::size_t N>
struct triangle {};

////////////////////////////////////////////////////////////////////////////////
//! \brief the triangle class
//! \remark this is the 2D specialization
////////////////////////////////////////////////////////////////////////////////
template<>
struct triangle<2> {

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::triangle;

  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename T >
  static auto centroid( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    return midpoint( pt0, pt1, pt2 );
  }

  //============================================================================
  //! \brief the midpoint is the same as the centroid
  //========================auto ===============================================
  template< typename T >
  static T midpoint( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto third = 
      static_cast<value_type>(1) / static_cast<value_type>(3);
    return { 
      third * ( pt0[0] + pt1[0] + pt2[0] ),  
      third * ( pt0[1] + pt1[1] + pt2[1] ),  
    };
  }

  //============================================================================
  //! \brief the volume function
  //============================================================================
  template< typename T >
  static auto area( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto half = 
      static_cast<value_type>(1) / static_cast<value_type>(2);
    T u{ pt1[0] - pt0[0], pt1[1] - pt0[1] };
    T v{ pt2[0] - pt0[0], pt2[1] - pt0[1] };
    auto cross = cross_product( u, v );
    return half * std::abs( cross );
  }
  
  //============================================================================
  //! \brief the normal of the triangle
  //============================================================================
  template< typename T >
  static T normal( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto half = 
      static_cast<value_type>(1) / static_cast<value_type>(2);
    T u{ pt1[0] - pt0[0], pt1[1] - pt0[1] };
    T v{ pt2[0] - pt0[0], pt2[1] - pt0[1] };
    auto cross = cross_product( u, v );
    return {0, half*cross};
  }
  
};



////////////////////////////////////////////////////////////////////////////////
//! \brief the triangle class
//! \remark this is the 3D specialization
////////////////////////////////////////////////////////////////////////////////
template<>
struct triangle<3> {

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::triangle;

  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename T >
  static auto centroid( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    return midpoint( pt0, pt1, pt2 );
  }

  //============================================================================
  //! \brief the midpoint is the same as the centroid
  //========================auto ===============================================
  template< typename T >
  static T midpoint( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto third = 
      static_cast<value_type>(1) / static_cast<value_type>(3);
    return { 
      third * ( pt0[0] + pt1[0] + pt2[0] ),  
      third * ( pt0[1] + pt1[1] + pt2[1] ),  
      third * ( pt0[2] + pt1[2] + pt2[2] ),  
    };
  }
  
  //============================================================================
  //! \brief the volume function
  //============================================================================
  template< typename T >
  static auto area( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto half = 
      static_cast<value_type>(1) / static_cast<value_type>(2);
    T u{ pt1[0] - pt0[0], pt1[1] - pt0[1], pt1[2] - pt0[2] };
    T v{ pt2[0] - pt0[0], pt2[1] - pt0[1], pt2[2] - pt0[2] };
    auto cross = cross_product( u, v );
    return half * math::abs( cross );
  }

  //============================================================================
  //! \brief the normal of the trianlge
  //============================================================================
  template< typename T >
  static auto normal( const T & pt0, const T & pt1, const T & pt2 ) 
  {
    using value_type = typename T::value_type;
    constexpr auto half = 
      static_cast<value_type>(1) / static_cast<value_type>(2);
    T u{ pt1[0] - pt0[0], pt1[1] - pt0[1], pt1[2] - pt0[2] };
    T v{ pt2[0] - pt0[0], pt2[1] - pt0[1], pt2[2] - pt0[2] };
    auto cross = cross_product( u, v );
    cross *= half;
    return cross;
  }
  
};

} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
