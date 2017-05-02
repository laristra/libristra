/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Loop through a list of tuples and apply a specific function.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "flecsi-sp/utils/detail/tuple_visit_impl.h"

namespace flecsi {
namespace sp {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
//! \brief Loop through a list of tuples and apply a specific function.
//! \param [in] f  A callable object.
//! \param [in,out] aTuple  The first tuple whose elements will get passed to \c f.
//! \param [in,out] aTuples The first tuple whose elements will get passed to \c f.
//! \remark f can be a functor which gets returned
////////////////////////////////////////////////////////////////////////////////
template<typename Callable, typename Head, typename... Tail>
Callable tuple_visit(Callable&& f, Head&& aTuple, Tail&&... aTail)
{
  constexpr auto size = std::tuple_size<typename std::remove_reference<Head>::type>::value;
  detail::visit_tuple_ws<size-1>::visit( std::forward<Callable>(f), 
                                         std::forward<Head>(aTuple), 
                                         std::forward<Tail>(aTail)... );
  return f;
}


} // namespace
} // namespace
} // namespace
