/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a function to create a tuple from an array.
////////////////////////////////////////////////////////////////////////////////

#pragma once

namespace ristra {
namespace utils {

namespace detail {

//! \brief An array helper type. 
template<typename T, typename... U>
using Array = std::array<T, 1+sizeof...(U)>;

//! \brief This is the main implementation that creates the array from 
//!        tuple values.
template<typename T, typename... U, std::size_t... I>
inline Array<T, U...>
to_array(const std::tuple<T, U...>& t, std::index_sequence<I...>)
{
  return Array<T, U...>{ get<I>(t)... };
}

} // detail

////////////////////////////////////////////////////////////////////////////////
//! \brief This is the main callable interface.  It creates an array
//!        from a tuple of values t.
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename... U>
inline detail::Array<T, U...>
to_array(const tuple<T, U...>& t)
{
  using IndexTuple = std::make_index_sequence<1+sizeof...(U)>;
  return detail::to_array(t, IndexTuple());
} 
 
} // namespace
} // namespace
