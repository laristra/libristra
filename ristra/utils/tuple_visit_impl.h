/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Loop through a list of tuples and apply a specific function.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <cstddef>
#include <tuple>


namespace ristra {
namespace utils {
namespace detail {

//! \brief support struct to iterate over the tuple(s)
template<std::size_t size>
struct visit_tuple_ws
{
  template<typename Callable, typename Head, typename... Tail>
  static void visit(Callable&& f, Head&& aTuple, Tail&&... aTail)
  {
    using std::get;
    visit_tuple_ws<size-1>::visit( std::forward<Callable>(f), 
                                   std::forward<Head>(aTuple), 
                                   std::forward<Tail>(aTail)... );
    f( get<size>( std::forward<Head>(aTuple) ), 
       get<size>( std::forward<Tail>(aTail) )...);
  }
};

//! \brief stop recursion here
template<>
struct visit_tuple_ws<0u>
{
  template<typename Callable, typename Head, typename... Tail>
  static void visit(Callable&& f, Head&& aTuple, Tail&&... aTail)
  {
    using std::get;
    f( get<0>( std::forward<Head>(aTuple) ), 
       get<0>( std::forward<Tail>(aTail) )...);
  }
};


} // namespace detail
} // namespace utils
} // namespace ristra
