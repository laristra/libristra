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


// user includes
#include "tuple_for_each_impl.h"

namespace ristra {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
//! \brief Exectute something for each element of a tuple
//! \remark this is my version
////////////////////////////////////////////////////////////////////////////////
template<class Tuple, class F>
void tuple_for_each( Tuple&& tup, F&& f ) {
  auto indexes = detail::get_indexes(tup);
  detail::tuple_for_each(indexes, std::forward<Tuple>(tup), std::forward<F>(f) );
}


} // namespace
} // namespace


