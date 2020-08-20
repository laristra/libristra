/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
/// 
/// \brief Some helper functions for zipping tupples together.
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <tuple>

namespace ristra {
namespace utils {
namespace detail {


//! helpers for generating sequences
template<size_t ...S>
struct seq { };

template<size_t N, size_t ...S>
struct gens : gens<N-1, N-1, S...> 
{ };

template<size_t ...S>
struct gens<0, S...> {
  using type = seq<S...>;
};

//! zip each tuple together
template <class Tup1, class Tup2, size_t ...S>
decltype(auto) tuple_zip_helper(Tup1&& t1, Tup2&& t2, seq<S...> s)  {
  using std::get;
  return std::make_tuple( std::make_pair( get<S>(t1), get<S>(t2) )...);
}


//! tie each tuple together
template <class Tup1, class Tup2, size_t ...S>
decltype(auto) tuple_tie_helper(Tup1&& t1, Tup2&& t2, seq<S...> s)  {
  using std::get;
  using std::forward_as_tuple;
  return std::make_tuple( forward_as_tuple( get<S>(t1), get<S>(t2) )...);
}

} // namespace
} // namespace
} // namespace
