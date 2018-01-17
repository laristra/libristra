/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief A static for-each function for looping over sequences statically.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <cstddef>
#include <utility>

namespace ristra {
namespace utils {

namespace detail {

//! \brief actuall call to functions
template<std::size_t... Is, class F>
void static_for( std::index_sequence<Is...>, F&& f ) {
  int unused[] = { 0, ( (void)f(Is), 0 )... };
}

} // namespace 


////////////////////////////////////////////////////////////////////////////////
//! \brief Statically loop over integers from 0 to N, executing a function f
////////////////////////////////////////////////////////////////////////////////
template<std::size_t N, class F>
void static_for(  F&& f ) {
  auto indexes = std::make_index_sequence<N>();
  detail::static_for(indexes, std::forward<F>(f) );
}



} // namespace
} // namespace
