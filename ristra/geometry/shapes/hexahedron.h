/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utility functions for hexahedrons.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/geometry/shapes/geometric_shapes.h"
#include "flecsi-sp/geometry/shapes/quadrilateral.h"

namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

////////////////////////////////////////////////////////////////////////////////
//! \brief the hexahedron class
////////////////////////////////////////////////////////////////////////////////
struct hexahedron {


  //============================================================================
  //! private utilities
  //============================================================================
private:


  //! \brief private centroid utitility
  template< class T, class U, class V, class W, class X >
  static constexpr 
  void centroid__( T & vol, U & cx, V & nsum, const W & vm, X && v )
  { 
    // nothing left to do
  }
  
  //! \brief private centroid utitility
  template< 
    class T, class U, class V, class W, class X1, class X2, class ... Args 
  >
  static constexpr 
  void centroid__( 
    T & vol, U & cx, V & nsum, const W & vm, X1 && v1, X2 && v2, Args&&... args 
  ) { 
   
    // get normal
    auto n = triangle<3>::normal( v1, v2, vm );
    nsum += n;
    // compute main contribution to centroid
    for ( int d=0; d<3; d++ ) {
      auto a1 = math::sqr( v1[d] + v2[d] );
      auto a2 = math::sqr( v2[d] + vm[d] );
      auto a3 = math::sqr( vm[d] + v1[d] );
      auto prod = (a1 + a2 + a3) * n[d];
      cx[d] += prod;
    }
    // dot with any coordinate for volume
    vol += dot_product( n, vm );
    // do next edge
    centroid__( 
      vol, cx, nsum, vm,
      std::forward<X2>(v2), 
      std::forward<Args>(args)... 
    ); 
  }  


  template< typename T, typename U >
  static void centroid_( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3,
    T & cx, U & vol, T & nsum
  ) {

    using point_type = T;
    using coord_type = typename T::value_type;

    // face midpoint
    auto xm = quadrilateral<3>::midpoint( pt0, pt1, pt2, pt3 );

    // call main implementation, sticking first point back on end
    centroid__( vol, cx, nsum, xm, pt0, pt1, pt2, pt3, pt0 );


  }

public:

  //============================================================================
  //! Public Defines
  //============================================================================

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::hexahedron;
  
  //============================================================================
  //! \brief the centroid function
  //============================================================================
  template< typename T >
  static auto centroid( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3,
    const T & pt4, const T & pt5, const T & pt6, const T & pt7 ) 
  {

    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;

    // initialize volume
    point_type cx(0), nsum(0);
    coord_type v = 0;

    //--------------------------------------------------------------------------
    // loop over faces

    centroid_( pt0, pt1, pt2, pt3, cx, v, nsum );
    centroid_( pt4, pt7, pt6, pt5, cx, v, nsum );
    centroid_( pt0, pt4, pt5, pt1, cx, v, nsum );
    centroid_( pt1, pt5, pt6, pt2, cx, v, nsum );
    centroid_( pt2, pt6, pt7, pt3, cx, v, nsum );
    centroid_( pt3, pt7, pt4, pt0, cx, v, nsum );

    // divide by volume
    cx /= 8 * v;

    //--------------------------------------------------------------------------
    // return result

    return cx;

  }

  //============================================================================
  //! \brief the midpoint function
  //============================================================================
  template< typename T >
  static T midpoint( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3,
    const T & pt4, const T & pt5, const T & pt6, const T & pt7
  ) {
    using value_type = typename T::value_type;
    constexpr auto eigth = 
      static_cast<value_type>(1) / static_cast<value_type>(8);
    return { 
      eigth * ( pt0[0] + pt1[0] + pt2[0] + pt3[0] + pt4[0] + pt5[0] + pt6[0] + pt7[0] ),  
      eigth * ( pt0[1] + pt1[1] + pt2[1] + pt3[1] + pt4[1] + pt5[1] + pt6[1] + pt7[1] ), 
      eigth * ( pt0[2] + pt1[2] + pt2[2] + pt3[2] + pt4[2] + pt5[2] + pt6[2] + pt7[2] ),      
    };
  }
  
  //============================================================================
  //! \brief the volume function
  //! \see Grandy, "Efficient Computation of Volume of Hexahedral Cells", 1997
  //============================================================================
  template< typename T >
  static auto volume( 
    const T & pt0, const T & pt1, const T & pt2, const T & pt3,
    const T & pt4, const T & pt5, const T & pt6, const T & pt7 ) 
  {
    // broken into tets that all share the midpoint, but faster (supposedly)
    // surface is broken into tets
    T d20{ pt2[0] - pt0[0], pt2[1] - pt0[1], pt2[2] - pt0[2] };
    T d50{ pt5[0] - pt0[0], pt5[1] - pt0[1], pt5[2] - pt0[2] };
    T d61{ pt6[0] - pt1[0], pt6[1] - pt1[1], pt6[2] - pt1[2] };
    T d63{ pt6[0] - pt3[0], pt6[1] - pt3[1], pt6[2] - pt3[2] };
    T d64{ pt6[0] - pt4[0], pt6[1] - pt4[1], pt6[2] - pt4[2] };
    T d70{ pt7[0] - pt0[0], pt7[1] - pt0[1], pt7[2] - pt0[2] };
    T d61_d70{ d61[0]+d70[0], d61[1]+d70[1], d61[2]+d70[2] };
    T d63_d50{ d63[0]+d50[0], d63[1]+d50[1], d63[2]+d50[2] };
    T d64_d20{ d64[0]+d20[0], d64[1]+d20[1], d64[2]+d20[2] };
    auto det = 
      std::abs( triple_product( d61_d70, d63, d20 ) ) +
      std::abs( triple_product( d70, d63_d50, d64 ) ) +
      std::abs( triple_product( d61, d50, d64_d20 ) );
    return det / 12;
  }
     
};

} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
