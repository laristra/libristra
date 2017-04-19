/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file polygon.h
/// \brief Some utility functions for polygons.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "geometric_shapes.h"
#include "triangle.h"
#include "../../math/general.h"

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
struct polygon {};


////////////////////////////////////////////////////////////////////////////////
//! \brief the polygon class
////////////////////////////////////////////////////////////////////////////////
template<>
struct polygon<2> {



  //============================================================================
  //! \brief private utilities
  //============================================================================

private:

  
  //! \brief private centroid utitility
  template< class T, class U, class V >
  static constexpr 
  void centroid_( T & cx, U & vol, V && v )
  { 
    // nothing left to do
  }
  
  //! \brief private centroid utitility
  template< class T, class U, class V1, class V2, class ... Args >
  static constexpr 
  void centroid_( T & cx, U & vol, V1 && v1, V2 && v2, Args&&... args )
  { 
    
    auto tmp = v1[0]*v2[1] - v2[0]*v1[1];
    cx[0] += ( v1[0] + v2[0] ) * tmp;
    cx[1] += ( v1[1] + v2[1] ) * tmp;
    vol += tmp;
    centroid_( cx, 
               vol, 
               std::forward<V2>(v2), 
               std::forward<Args>(args)... ); 
  }  

  //! \brief area operator.
  template< class U, class V >
  static constexpr 
  void area_( U & vol, V && v )
  { 
    // nothing left to do
  }

  //! \brief average operator.
  template< class U, class V1, class V2, class ... Args >
  static constexpr 
  void area_( U & vol, V1 && v1, V2 && v2, Args&&... args )
  { 
  
    vol += v1[0]*v2[1] - v2[0]*v1[1];
    area_( vol, 
           std::forward<V2>(v2), 
           std::forward<Args>(args)... ); 
  }


public:

  //============================================================================
  //! \brief the shape identifier
  //============================================================================
  static constexpr auto shape = geometric_shapes_t::polygon;


  //============================================================================
  //! \brief compute midpoint for 2d polygons
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< typename... Args >
  static 
  constexpr
  auto midpoint( Args&&... args ) 
  {
    return math::average( std::forward<Args>(args)... );
  }


  //============================================================================
  //! \brief compute midpoint for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto midpoint( InputIt && first, InputIt && last )
  { 
    return math::average( std::forward<InputIt>(first), 
                          std::forward<InputIt>(last) );
  }

  //============================================================================
  //! \brief compute midpoint for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto midpoint( const V<T, Args...> & points )
  { 
    return midpoint( points.begin(), points.end() );
  }

  //============================================================================
  //! \brief compute centroid for 2d polygons
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< typename T, typename... Types >
  static 
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 2 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 2), 
    std::decay_t<T> 
  >
  centroid( T && t, Types&&... args ) 
  {
    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;
    // initialize centroid and volume
    point_type cx( 0 );
    coord_type vol(0);
    // call main implementation, sticking first point back on end
    centroid_( cx, vol, 
               std::forward<T>(t), 
               std::forward<Types>(args)..., 
               std::forward<T>(t) );
    cx /=  3 * vol; // divide by volume
    return cx;
  }


  //============================================================================
  //! \brief compute centroid for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto centroid( InputIt first, InputIt last )
  { 

    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 2 && "not enough points for 2d" );
    
    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    point_type cx(0);
    coord_type a(0);
    
    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      auto tmp = (*po)[0]*(*pn)[1] - (*pn)[0]*(*po)[1];
      a += tmp;
      cx[0] += tmp * ( (*po)[0] + (*pn)[0] );
      cx[1] += tmp * ( (*po)[1] + (*pn)[1] );
      po = pn;
    }
    
    cx /= 3 * a;
    
    return cx;
  }

  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto centroid( const V<T, Args...> & points )
  { 
    return centroid( points.begin(), points.end() );
  }

  
  //============================================================================
  //! \brief compute area for 2d
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< class T, class... Types >
  static
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 2 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 2), 
     std::decay_t< decltype( std::declval<T>()[0] ) > 
  >
  area( T && t, Types&&... args )
  { 
    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;
    // initialize area
    coord_type area(0);
    // call main implementation, sticking first point back on end
    area_( area, 
           std::forward<T>(t), 
           std::forward<Types>(args)..., 
           std::forward<T>(t) );
    return std::abs(area/2);
  }
  

  //============================================================================
  //! \brief compute area for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto area( InputIt first, InputIt last )
  { 

    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 2 && "not enough points for 2d" );

    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    coord_type a(0);

    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      a += (*po)[0]*(*pn)[1] - (*pn)[0]*(*po)[1];
      po = pn;
    }
    return std::abs(a/2);
  }
  
  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto area( const V<T, Args...> & points )
  { 
    return area( points.begin(), points.end() );
  }

  
  //============================================================================
  //! \brief compute normal for 2d
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< class T, class... Types >
  static
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 2 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 2), 
     std::decay_t<T> 
  >
  normal( T && t, Types&&... args )
  { 
    using point_type = typename std::decay_t<T>;
    using coord_type = typename point_type::value_type;

    // initialize normal
    coord_type area(0);
    // call main implementation, sticking first point back on end
    area_( area, 
           std::forward<T>(t), 
           std::forward<Types>(args)..., 
           std::forward<T>(t) );
    return point_type{0, area/2};
  }
  

  //============================================================================
  //! \brief compute normal for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto normal( InputIt first, InputIt last )
  { 

    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 2 && "not enough points for 2d" );

    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    coord_type a(0);

    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      a += (*po)[0]*(*pn)[1] - (*pn)[0]*(*po)[1];
      po = pn;
    }
    return point_type{ 0, a/2 };
  }
  
  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto normal( const V<T, Args...> & points )
  { 
    return normal( points.begin(), points.end() );
  }
     
};


////////////////////////////////////////////////////////////////////////////////
//! \brief the polygon class
////////////////////////////////////////////////////////////////////////////////
template<>
struct polygon<3> {


  //============================================================================
  //! \brief private utilities
  //============================================================================

private:

  
  //! \brief private area utitility
  template< class T, class U, class V >
  static constexpr 
  void area_( T & vol, U & vm, V && v )
  { 
    // nothing left to do
  }
  
  //! \brief private area utitility
  template< class T, class U, class V1, class V2, class ... Args >
  static constexpr 
  void area_( T & vol, const U & vm, V1 && v1, V2 && v2, Args&&... args )
  { 
    
    vol += triangle<3>::area( v1, v2, vm );
    area_( vol, 
           vm, 
           std::forward<V2>(v2), 
           std::forward<Args>(args)... ); 
  }  


  
  //! \brief private centroid utitility
  template< class T, class U, class V0, class V >
  static constexpr 
  void centroid_( T & vol, U & cx, const V0 & vm, V && v )
  { 
    // nothing left to do
  }
  
  //! \brief private centroid utitility
  template< class T, class U, class V0, class V1, class V2, class ... Args >
  static constexpr 
  void centroid_( T & vol, U & cx, const V0 & vm, V1 && v1, V2 && v2, Args&&... args )
  { 
   
    auto tmp_vol = triangle<3>::area( v1, v2, vm );
    auto tmp_cx  = triangle<3>::centroid( v1, v2, vm );
    vol += tmp_vol;
    for ( int d=0; d<3; ++d ) cx[d] += tmp_vol * tmp_cx[d];
    centroid_( vol, 
               cx, 
               vm,
               std::forward<V2>(v2), 
               std::forward<Args>(args)... ); 
  }  


  
  //! \brief private centroid utitility
  template< class T, class U, class V >
  static constexpr 
  void normal_( T & n, const U & vm, V && v )
  { 
    // nothing left to do
  }
  
  //! \brief private centroid utitility
  template< class T, class U, class V1, class V2, class ... Args >
  static constexpr 
  void normal_( T & n, const U & vm, V1 && v1, V2 && v2, Args&&... args )
  { 
   
    n += triangle<3>::normal( v1, v2, vm );
    normal_( n, 
             vm,
             std::forward<V2>(v2), 
             std::forward<Args>(args)... ); 
  }  

public:

  //============================================================================
  //! \brief the shape identifier
  //============================================================================
  static constexpr auto shape = geometric_shapes_t::polygon;

  //============================================================================
  //! \brief compute midpoint for 2d polygons
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< typename... Args >
  static 
  constexpr
  auto midpoint( Args&&... args ) 
  {
    return math::average( std::forward<Args>(args)... );
  }


  //============================================================================
  //! \brief compute midpoint for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto midpoint( InputIt && first, InputIt && last )
  { 
    return math::average( std::forward<InputIt>(first), 
                          std::forward<InputIt>(last) );
  }

  //============================================================================
  //! \brief compute midpoint for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto midpoint( const V<T, Args...> & points )
  { 
    return midpoint( points.begin(), points.end() );
  }


  //============================================================================
  //! \brief compute centroid for 2d polygons
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< typename T, typename... Types >
  static 
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 3 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 3), 
    std::decay_t<T> 
  >
  centroid( T && t, Types&&... args ) 
  {
    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;
    // initialize centroid and volume
    point_type cx( 0 );
    coord_type vol(0);
    // get the centroid
    auto xm = midpoint( std::forward<T>(t), std::forward<Types>(args)... );
    // call main implementation, sticking first point back on end
    centroid_( vol, cx, 
               xm,
               std::forward<T>(t), 
               std::forward<Types>(args)..., 
               std::forward<T>(t) );
    cx /=  vol; // divide by volume
    return cx;
  }


  //============================================================================
  //! \brief compute centroid for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto centroid( InputIt && first, InputIt && last )
  { 
    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 3 && "not enough points for 3d" );

    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    // get the midpoint
    auto xm = midpoint( first, last );

    // initialize area
    point_type cx(0);
    coord_type a(0);

    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      auto tmp_a  = triangle<3>::area( (*po), (*pn), xm );
      auto tmp_cx = triangle<3>::centroid( (*po), (*pn), xm );
      a += tmp_a;
      for ( int d=0; d<3; ++d ) cx[d] += tmp_a * tmp_cx[d];
      po = pn;
    }
    cx /= a;
    return cx;

  }

  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto centroid( const V<T, Args...> & points )
  { 
    return centroid( points.begin(), points.end() );
  }

  
  //============================================================================
  //! \brief compute area for 2d
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< class T, class... Types >
  static
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 3 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 3), 
     std::decay_t< decltype( std::declval<T>()[0] ) > 
  >
  area( T && t, Types&&... args )
  { 
    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;
    // initialize area
    coord_type area(0);
    // get the centroid
    auto xm = midpoint( std::forward<T>(t), std::forward<Types>(args)... );
    // call main implementation, sticking first point back on end
    area_( area, 
           xm,
           std::forward<T>(t), 
           std::forward<Types>(args)..., 
           std::forward<T>(t) );
    return area;
  }
  

  //============================================================================
  //! \brief compute area for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto area( InputIt first, InputIt last )
  { 

    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 3 && "not enough points for 3d" );

    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    // get the centroid
    auto xm = midpoint( first, last );

    // initialize area
    coord_type a(0);

    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      a += triangle<3>::area( *po, *pn, xm );
      po = pn;
    }
    return a;
  }
  
  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto area( const V<T, Args...> & points )
  { 
    return area( points.begin(), points.end() );
  }
     
  //============================================================================
  //! \brief compute normal for 2d
  //! \remark all arguments must be of the same type
  //! \remark this one is used for three or more arguments
  //============================================================================
  template< class T, class... Types >
  static
  constexpr
  std::enable_if_t< 
    (sizeof...(Types) >= 3 && utils::are_type_t<T,Types...>::value && 
     std::decay_t<T>::size() >= 3), 
     std::decay_t<T> 
  >
  normal( T && t, Types&&... args )
  { 
    using point_type = std::decay_t<T>;
    using coord_type = typename point_type::value_type;
    // initialize normal
    point_type n(0);
    // get the centroid
    auto xm = midpoint( std::forward<T>(t), std::forward<Types>(args)... );
    // call main implementation, sticking first point back on end
    normal_( n, 
             xm,
             std::forward<T>(t), 
             std::forward<Types>(args)..., 
             std::forward<T>(t) );
    return n;
  }
  

  //============================================================================
  //! \brief compute normal for 2d polygons
  //! \remark this one is used for iterators
  //============================================================================
  template< typename InputIt >
  static 
  auto normal( InputIt first, InputIt last )
  { 

    // get the number of points
    auto num_points = std::distance( first, last );
    assert( num_points > 3 && "not enough points for 3d" );

    // determine the vector and coordinate type
    using point_type = std::decay_t< decltype(*first) >;
    using coord_type = std::decay_t< decltype( (*first)[0] ) >;

    // get the centroid
    auto xm = midpoint( first, last );

    // initialize normal
    point_type n(0);

    auto po = std::prev( last );
    for ( auto pn = first; pn!=last; ++pn ) {
      n += triangle<3>::normal( *po, *pn, xm );
      po = pn;
    }
    return n;
  }
  
  //============================================================================
  //! \brief compute centroid for 2d or 3d
  //! \remark this is a runtime computation
  //============================================================================
  template< 
    typename T, typename... Args, 
    template <typename, typename...> class V 
  >
  static 
  auto normal( const V<T, Args...> & points )
  { 
    return normal( points.begin(), points.end() );
  }
     
};

} // namspeace shapes
} // namespace geom
} // namespace ale
} // namespace ale
