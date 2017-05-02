/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a default operators for fundamental types.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// user includes
#include "flecsi-sp/math/detail/general_impl.h"

#include "flecsi-sp/utils/errors.h"
#include "flecsi-sp/utils/template_helpers.h"
#include "flecsi-sp/utils/type_traits.h"

// system includes
#include <algorithm> 
#include <cassert>
#include <numeric>
#include <cmath>

namespace flecsi {
namespace sp {
namespace math {


//////////////////////////////////////////////////////////////////////////////
// Compute an average
//////////////////////////////////////////////////////////////////////////////

//! \brief average operator.
//! \remark all arguments must be of the same type
//! \remark this one is used for three or more arguments
template< class T, class... Types >
constexpr
std::enable_if_t< 
  (sizeof...(Types) > 1) && 
  utils::are_type_t<T,Types...>::value, std::decay_t<T> >
average( T && t, Types&&... args )
{ 
  auto res( t ); // first one
  detail::average(res, std::forward<Types>(args)...); // sum the rest
  res /=  ( sizeof...(args) + 1 ); // divide by number
  return res;
}

//! \brief average operator.
//! \remark all arguments must be of the same type
//! \remark this one is used for two arguments only
template< class T, class U >
constexpr 
std::enable_if_t< utils::are_type_t<T,U>::value, std::decay_t<T> >
average( T && t, U && u )
{ 
  return ( std::forward<T>(t) + std::forward<T>(u) ) / 2;
}

//! \brief average operator.
//! \remark all arguments must be of the same type
//! \remark this function gives an error because not all values are the same type
template< class T, class... Types >
constexpr
std::enable_if_t< 
  !utils::are_type_t<T,Types...>::value, std::decay_t<T> >
average( T && t, Types&&... args )
{ 
  static_assert(     
    utils::are_type_t<T,Types...>::value, 
    "All parameters parameter need to be the same type." );
  return T();
}

//! \brief average operator.
//! \remark all arguments must be of the same type
template< 
  typename T, typename... Args, 
  template <typename, typename...> class V 
>
auto average( const V<T, Args...> & vals )
{ 
  assert( vals.size() > 0 && "not enough values" );
  T avg(0);
  for ( const auto & x : vals ) avg += x;
  avg /= vals.size();
  return avg;
}

//! \brief average operator.
//! \remark all arguments must be of the same type
template< 
  typename InputIt,
  typename = typename std::enable_if_t< utils::is_iterator_v<InputIt> >
>
auto average( InputIt first, InputIt last )
{ 
  auto num = std::distance( first, last );
  assert( num > 0 && "not enough values" );
    
  using value_type = std::decay_t< decltype(*first) >;

  value_type avg(0);
  for ( auto it=first; it!=last; ++it ) avg += (*it);
  avg /= num;
  return avg;
}

//////////////////////////////////////////////////////////////////////////////
// return the max and min value of lists
//////////////////////////////////////////////////////////////////////////////

//! \brief return the minimum value of a list
//! \param [in] a the array to search
//! \remark general version
//! @{
template< template<typename...> class C, typename...Args >
auto min_element( const C<Args...> & a ) 
{
  return std::min_element( a.begin(), a.end() );
}

template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A
 >
auto min_element( const A<T,N...> & a ) 
{
  return std::min_element( a.begin(), a.end() );
}
//! @}

//! \brief return the maximum value of a list
//! \param [in] a the array to search
//! \remark general version
//! @{
template< template<typename...> class C, typename...Args >
auto max_element( const C<Args...> & a ) 
{
  return std::max_element( a.begin(), a.end() );
}

template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A
 >
auto max_element( const A<T,N...> & a ) 
{
  return std::max_element( a.begin(), a.end() );
}

//! @}

//////////////////////////////////////////////////////////////////////////////
// A dot product function
//////////////////////////////////////////////////////////////////////////////

//! \brief Compute the dot product
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
//! @{
template< class InputIt1, class InputIt2 >
auto dot_product( InputIt1 first1, InputIt1 last1, InputIt2 first2 )
{
  std::decay_t< decltype(*first1) > zero = 0;
  return std::inner_product(first1, last1, first2, zero );
}

template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A,
  std::size_t Len = utils::multiply( N... )
 >
T dot_product(const A<T, N...> &a, const A<T, N...> &b) 
{
  T dot = 0;
  for( utils::select_counter_t<Len> i = 0; i<Len; ++i )
    dot += a[i]*b[i];
  return dot;
}


template< template<typename...> class C, typename T, typename...Args >
T dot_product(const C<T,Args...> &a, const C<T,Args...> &b) 
{
  auto dot = dot_product( a.begin(), a.end(), b.begin() );
  return dot;
}
//! @}

//////////////////////////////////////////////////////////////////////////////
// magnitude of vectors
//////////////////////////////////////////////////////////////////////////////

//! \brief Compute the magnitude of the vector
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
//! @{
template< template<typename...> class C, typename T, typename...Args >
T magnitude(const C<T,Args...> &a) 
{
  return std::sqrt( dot_product(a,a) );
}

template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A,
  std::size_t Len = utils::multiply( N... )
 >
T magnitude(const A<T, N...> &a) 
{
  T abs = 0;
  for( utils::select_counter_t<Len> i = 0; i<Len; ++i )
    abs += a[i]*a[i];
  return std::sqrt(abs);
}

template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A
 >
T abs(const A<T, N...> &a) 
{
  return magnitude(a);
}

template< template<typename...> class C, typename T, typename...Args >
T abs(const C<T,Args...> &a) 
{
  return magnitude(a);
}
//! @}

//! \brief Compute the magnitude of the difference between two vectors
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
template< 
  typename T1, 
  typename T2, 
  std::size_t... N,
  template< typename, std::size_t... > class A,
  std::size_t Len = utils::multiply( N... )
 >
auto delta_magnitude(const A<T1, N...> &a, const A<T2, N...> &b) 
{
  decltype(a[0]*b[0]) abs = 0;
  for( utils::select_counter_t<Len> i = 0; i<Len; ++i ) {
    auto del = a[i] - b[i];
    abs += del*del;
  }
  return std::sqrt(abs);
}


//////////////////////////////////////////////////////////////////////////////
// Elementwise min and max
//////////////////////////////////////////////////////////////////////////////

//! \brief Compute the elementwise min
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
//! @{
template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A,
  std::size_t Len = utils::multiply( N... )
 >
auto min(const A<T, N...> &a, const A<T, N...> &b) 
{
  A<T, N...> tmp;
  for( utils::select_counter_t<Len> i = 0; i<Len; ++i )
    tmp[i] = std::min( a[i], b[i] );
  return tmp;
}

template< template<typename...> class C, typename T, typename...Args >
auto min(const C<T,Args...> &a, const C<T,Args...> &b) 
{
  C<T,Args...> tmp;
  for ( common::counter_t i=0; i<a.size(); i++ )
    tmp[i] = std::min( a[i], b[i] );
  return tmp;
}
//! @}

//! \brief Compute the elementwise max
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
template< 
  typename T, std::size_t... N,
  template< typename, std::size_t... > class A,
  std::size_t Len = utils::multiply( N... )
 >
auto max(const A<T, N...> &a, const A<T, N...> &b) 
{
  A<T, N...> tmp;
  for( utils::select_counter_t<Len> i = 0; i<Len; ++i )
    tmp[i] = std::max( a[i], b[i] );
  return tmp;
}

template< template<typename...> class C, typename T, typename...Args >
auto max(const C<T,Args...> &a, const C<T,Args...> &b) 
{
  C<T,Args...> tmp;
  for ( common::counter_t i=0; i<a.size(); i++ )
    tmp[i] = std::max( a[i], b[i] );
  return tmp;
}


//////////////////////////////////////////////////////////////////////////////
// Some general math functions
//////////////////////////////////////////////////////////////////////////////

//! \brief square operator.
template< class T >
constexpr auto sqr( T && x )
{ return std::forward<T>(x) * std::forward<T>(x); }

//! \brief returns 1 if +ve, -1 if -ve
template <typename T> 
constexpr int sgn( const T & val ) {
  return (T(0) < val) - (val < T(0));
}




////////////////////////////////////////////////////////////////////////////////
// compute the normalized vector
////////////////////////////////////////////////////////////////////////////////

//! \brief Compute the unit vector given a vector
//! \tparam T  The base value type.
//! \tparam D  The matrix/array dimension.
//! \param[in] mat  The matrix
//! \param[in] vec  The vector
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
C<T,D> unit( const C<T,D> & x )
{
  auto l = abs(x);
  auto u = x / l;
  return u;
}
  
////////////////////////////////////////////////////////////////////////////////
// compute the normal between two vectors
////////////////////////////////////////////////////////////////////////////////

//! \brief Compute the normal between two points
//! \tparam T  The array base value type.
//! \param[in] a  The first point
//! \param[in] b  The other point
//! \return The result of the operation
template < 
  typename T,
  template<typename, std::size_t> class C
>
C<T, 2> normal(const C<T, 2> &a, const C<T, 2> &b) 
{
  return { a[1] - b[1], b[0] - a[0] };
}

//! \brief Compute the normal between two points
//! \tparam T  The array base value type.
//! \param[in] a  The first point
//! \param[in] b  The other point
//! \return The result of the operation
template < 
  typename T,
  template<typename, std::size_t> class C
>
C<T, 3> normal(const C<T, 3> &a, const C<T, 3> &b) 
{
  raise_runtime_error("you should never get here");
  return { 0, 0, 0 }; // FIXME - this is here as a hack
}

////////////////////////////////////////////////////////////////////////////////
// compute the cross product
////////////////////////////////////////////////////////////////////////////////

//! \brief Compute the cross product
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
template < 
  typename T,
  template<typename, std::size_t> class C
>
T cross_product(const C<T, 2> &a, const C<T, 2> &b) 
{
  return a[0]*b[1] - a[1]*b[0];
}

//! \brief Compute the cross product
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
template < 
  typename T,
  template<typename, std::size_t> class C
>
auto cross_product(const C<T, 3> &a, const C<T, 3> &b) 
{
  C<T, 3> tmp;
  tmp[0] = a[1]*b[2] - a[2]*b[1];
  tmp[1] = a[2]*b[0] - a[0]*b[2];
  tmp[2] = a[0]*b[1] - a[1]*b[0];
  return tmp;
}

////////////////////////////////////////////////////////////////////////////////
// compute the triple product
////////////////////////////////////////////////////////////////////////////////

//! \brief Compute the cross product
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in] a  The first vector
//! \param[in] b  The other vector
//! \return The result of the operation
template < 
  typename T,
  template<typename, std::size_t> class C
>
T triple_product(const C<T, 3> &a, const C<T, 3> &b, const C<T, 3> &c) 
{
  return 
    a[0]*b[1]*c[2] + b[0]*c[1]*a[2] + c[0]*a[1]*b[2] -
    a[2]*b[1]*c[0] - b[2]*c[1]*a[0] - c[2]*a[1]*b[0];;
}


} // namespace
} // namespace
} // namespace
