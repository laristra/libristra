/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Provides a dimensioned array which functions as a vector.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// user includes
#include "array.h"

namespace flecsi {
namespace sp {
namespace math {

////////////////////////////////////////////////////////////////////////////////
//!  \brief An alias of the dimensioned array type.
//!
//!  \tparam T The type of the array, e.g., P.O.D. type.
//!  \tparam D The dimension of the array, i.e., the number of elements
//!    to be stored in the array.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t D> 
using vector = array<T,D>;


////////////////////////////////////////////////////////////////////////////////
//! \brief Reflect a vector about a plane given a normal to that plane.
//! \tparam T  The base value type.
//! \tparam D  The array dimension.
//! \param [in] v  The vector to reflect.
//! \param [in] n  The normal of the plane to reflect in.
////////////////////////////////////////////////////////////////////////////////
template < 
  typename T, std::size_t D,
  template<typename, std::size_t> class C
>
C<T,D> reflect( const C<T,D> & v, const C<T,D> & n ) {

  auto dot = dot_product( v, n );

  auto rot = n;
  rot *= 2 * dot;

  auto tmp = v;
  tmp -= rot;

  return tmp;
}

} // namespace
} // namespace
} // namespace
