/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a tuple type which functions like a vector.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "ristra/utils/tuple_for_each.h"
#include "ristra/utils/tuple_visit.h"
#include "ristra/utils/tuple_zip.h"

// system includes
#include <iostream>
#include <tuple>

namespace ristra {
namespace math {

////////////////////////////////////////////////////////////////////////////////
//!  \brief Provides a tuple that functions like a mathematical array.
//!
//!  \tparam Types  The types of the tuple, e.g., P.O.D. type.
////////////////////////////////////////////////////////////////////////////////
template <typename... Types>
using tuple = std::tuple<Types...>;

//! \brief use std::get for access of tuple_t
using std::get;

//! \brief Constructor with one value.
//! \param[in] val The value to set the array to
template < typename... Types, typename U >
void fill( tuple<Types...> & t, const U & val ) 
{ 
  //std::cout << "tuple (single value constructor)\n";
  using std::fill;  // enable ADL
  utils::tuple_for_each( t, 
                         [&](auto & tup) { 
                           tup = val; 
                         } );
}


//! \brief Add to a tuple.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! @{
template <typename... Types>
void plus_equal( tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  utils::tuple_for_each( utils::tuple_tie( lhs, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<0>(tup) + get<1>(tup);
                         } );                        
}

template <typename... Types, typename U>
void plus_equal( tuple<Types...>& lhs, const U & rhs )
{
  utils::tuple_for_each( lhs,
                         [&](auto & tup) { 
                           tup = tup + rhs;
                         } );                        
}
//! @}

//! \brief Addition operator involving tuples.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! \return The result of the operation.
//! @{
template <typename... Types>
auto operator+( const tuple<Types...>& lhs, 
                const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_visit( 
                     [](auto & a, const auto & b, const auto & c) { 
                       a = b + c;
                     },
                     tmp, lhs, rhs );
  return tmp;
}

template <typename... Types, typename U>
auto operator+( const tuple<Types...>& lhs, const U & rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, lhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<1>(tup) + rhs;
                         } );                        
  return tmp;
}

template <typename... Types, typename U>
auto operator+( const U & lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = lhs + get<1>(tup);
                         } );                        
  return tmp;
}
//! @}


//! \brief Subtract a tuple.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! @{
template <typename... Types>
void minus_equal( tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  utils::tuple_for_each( utils::tuple_tie( lhs, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<0>(tup) - get<1>(tup);
                         } );                        
}

template <typename... Types, typename U>
void minus_equal( tuple<Types...>& lhs, const U & rhs )
{
  utils::tuple_for_each( lhs,
                         [&](auto & tup) { 
                           tup = tup - rhs;
                         } );                        
}
//! @}

//! \brief Subtraction operator involving tuples.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! \return The result of the operation.
//! @{
template <typename... Types>
auto operator-( const tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_visit( 
                     [](auto & a, const auto & b, const auto & c) { 
                       a = b - c;
                     },
                     tmp, lhs, rhs );
  return tmp;
}

template <typename... Types, typename U>
auto operator-( const tuple<Types...>& lhs, const U & rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, lhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<1>(tup) - rhs;
                         } );                        
  return tmp;
}

template <typename... Types, typename U>
auto operator-( const U & lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = lhs - get<1>(tup);
                         } );                        
  return tmp;
}
//! @}

//! \brief Multiply a tuple.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! @{
template <typename... Types>
void multiplies_equal( tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  utils::tuple_for_each( utils::tuple_tie( lhs, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<0>(tup) * get<1>(tup);
                         } );                        
}

template <typename... Types, typename U>
void multiplies_equal( tuple<Types...>& lhs, const U & rhs )
{
  utils::tuple_for_each( lhs,
                         [&](auto & tup) { 
                           tup = tup * rhs;
                         } );                        
}
//! @}

//! \brief Multiplication operator involving tuples.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! \return The result of the operation.
//! @{
template <typename... Types>
auto operator*( const tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_visit( 
                     [](auto & a, const auto & b, const auto & c) { 
                       a = b * c;
                     },
                     tmp, lhs, rhs );
  return tmp;
}

template <typename... Types, typename U>
auto operator*( const tuple<Types...>& lhs, const U & rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, lhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<1>(tup) * rhs;
                         } );                        
  return tmp;
}

template <typename... Types, typename U>
auto operator*( const U & lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = lhs * get<1>(tup);
                         } );                        
  return tmp;
}
//! @}




//! \brief Divide a tuple.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! @{
template <typename... Types>
void divides_equal( tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  utils::tuple_for_each( utils::tuple_tie( lhs, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<0>(tup) / get<1>(tup);
                         } );                        
}

template <typename... Types, typename U>
void divides_equal( tuple<Types...>& lhs, const U & rhs )
{
  utils::tuple_for_each( lhs,
                         [&](auto & tup) { 
                           tup = tup / rhs;
                         } );                        
}
//! @}

//! \brief Division operator involving tuples.
//! \param[in] lhs The value on the left hand side of the operator.
//! \param[in] rhs The value on the right hand side of the operator.
//! \return The result of the operation.
//! @{
template <typename... Types>
auto operator/( const tuple<Types...>& lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_visit( 
                     [](auto & a, const auto & b, const auto & c) { 
                       a = b / c;
                     },
                     tmp, lhs, rhs );
  return tmp;
}

template <typename... Types, typename U>
auto operator/( const tuple<Types...>& lhs, const U & rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, lhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = get<1>(tup) / rhs;
                         } );                        
  return tmp;
}

template <typename... Types, typename U>
auto operator/( const U & lhs, const tuple<Types...>& rhs )
{
  tuple< std::decay_t<Types>... > tmp;
  utils::tuple_for_each( utils::tuple_tie( tmp, rhs ),
                         [&](auto tup) { 
                           using std::get;
                           get<0>(tup) = lhs / get<1>(tup);
                         } );                        
  return tmp;
}
//! @}



//! \brief Output operator for tuple.
//! \tparam T  The array base value type.
//! \tparam D  The array dimension.
//! \param[in,out] os  The ostream to dump output to.
//! \param[in]     rhs The tuple on the right hand side of the operator.
//! \return A reference to the current ostream.
template <typename... Types>
auto & operator<<(std::ostream& os, const tuple<Types...>& a)
{
  os << "{";
  utils::tuple_for_each( a, 
                          [&os](auto & tup) { os << " [ " << tup << " ]"; } );
  os << " }";
  return os;
}
  

} // namespace
} // namespace
