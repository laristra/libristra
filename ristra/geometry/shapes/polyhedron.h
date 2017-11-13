/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utility functions for polyhedrons.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/geometry/shapes/geometric_shapes.h"
#include "flecsi-sp/geometry/shapes/triangle.h"
#include "flecsi-sp/math/general.h"
#include "flecsi-sp/utils/array_ref.h"

namespace flecsi {
namespace sp {
namespace geometry {
namespace shapes {

////////////////////////////////////////////////////////////////////////////////
//! \brief the polyhedron class
//! \see Stroud, Approximate calculation of multiple integrals, 
//!      Prentice-Hall Inc., 1971.
////////////////////////////////////////////////////////////////////////////////
template< typename P >
class polyhedron {

public:

  //============================================================================
  // Typedefs
  //============================================================================

  //! \brief the shape identifier
  static constexpr auto shape = geometric_shapes_t::polyhedron;

  //! \brief the point and coordinate types
  using point_type = P;
  using coord_type = typename point_type::value_type;

  //============================================================================
  //! \brief insert a face into the polyhedron
  //============================================================================
  void insert( utils::array_ref<P> points ) 
  {
    insert( points.begin(), points.end() );
  }

  template< typename T >
  void insert( std::initializer_list<T> points ) 
  {
    insert( points.begin(), points.end() );
  }

  template< typename InputIt >
  void insert( InputIt first, InputIt last ) 
  {
    // copy the points
    std::vector< point_type > points( first, last );
    // move into the vector
    faces_.emplace_back( std::move(points) );
  }


  //============================================================================
  //! \brief the volume function
  //============================================================================
  auto centroid() const
  {
    // initialize volume
    point_type cx(0), nsum(0);
    coord_type v = 0;

    //--------------------------------------------------------------------------
    // loop over faces
    for ( const auto & points : faces_ ) {

      // face midpoint
      auto xm = math::average( points );

      // for each face edge
      auto po = std::prev( points.end() );
      for ( auto pn=points.begin(); pn!=points.end(); pn++ ) {
        // get normal
        auto n = triangle<3>::normal( *po, *pn, xm );
        nsum += n;
        // compute main contribution
        auto a1 = *po + *pn;
        auto a2 = *pn +  xm;
        auto a3 =  xm + *po;
        a1 *= a1;
        a2 *= a2;
        a3 *= a3;
        auto prod = a1;
        prod += a2;
        prod += a3;
        // multiply by the normal
        prod *= n;
        // add contribution to centroid
        cx += prod;
        // dot with any coordinate for volume
        v += dot_product( n, xm );
        // store old point
        po = pn;
      }
        
    }

    //--------------------------------------------------------------------------
    // return result

    // divide by volume
    cx /= 8 * v;

#if 0
    for ( auto & nx : nsum )
      assert( nx == 0 );
#endif 

    return cx;
  }

  //============================================================================
  //! \brief the midpoint function
  //============================================================================
  auto midpoint() const
  {
    // initialize volume
    point_type cx(0);

    //--------------------------------------------------------------------------
    // loop over faces
    
    for ( const auto & points : faces_ ) {
      // face midpoint
      auto xm = math::average( points );
      // add face contibution
      cx += xm;
    }

    //--------------------------------------------------------------------------
    // return result

    // divide by number of faces
    cx /= faces_.size();

    return cx;
  }

  //============================================================================
  //! \brief the midpoint 
  //============================================================================
  template< typename... Args >
  static auto midpoint( Args&&... pts ) 
  {
    return math::average( std::forward<Args>(pts)... );
  }

  //============================================================================
  //! \brief the volume function
  //============================================================================
  auto volume() const
  {

    // initialize volume
    coord_type v = 0;

    //--------------------------------------------------------------------------
    // loop over faces
    for ( const auto & points : faces_ ) {

      // face midpoint
      auto xm = math::average( points );

      // for each face edge
      auto po = std::prev( points.end() );
      for ( auto pn=points.begin(); pn!=points.end(); pn++ ) {
        // get normal
        auto n = triangle<3>::normal( *po, *pn, xm );
        // dot with any coordinate
        v += dot_product( n, xm );
        // store old point
        po = pn;
      }
        
    }

    //--------------------------------------------------------------------------
    // return result

    return std::abs(v) / 3;
  }
  
    
  //============================================================================
  // Private Data
  //============================================================================
private:

  //! the coordinates of each face
  std::vector< std::vector<point_type> > faces_;

};

} // namespace shapes
} // namespace geom
} // namespace ale
} // namespace ale
