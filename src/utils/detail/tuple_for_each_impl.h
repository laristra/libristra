/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
///  
/// \brief A static for-each function for looping over tuples statically.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <utility>

namespace ristra {
namespace utils {
namespace detail {

//! \brief create index list
template<class T>
constexpr std::make_index_sequence<std::tuple_size<T>::value>
get_indexes( T const& )
{ return {}; }

//! \brief actuall call to functions
template<std::size_t... Is, class Tuple, class F>
void tuple_for_each( std::index_sequence<Is...>, Tuple&& tup, F&& f ) {
  using std::get;
  int unused[] = { 0, ( (void)f(get<Is>(std::forward<Tuple>(tup))), 0 )... };
}



} // namespace
} // namespace
} // namespace
