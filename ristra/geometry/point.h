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
#include <ristra/math/vector.h>

// system includes
#include <cmath>

namespace ristra  {
namespace geometry {


////////////////////////////////////////////////////////////////////////////////
//!  \brief The dimensioned_array type provides a general base for defining
//!  contiguous array types that have a specific dimension.
//!
//!  \tparam T The type of the array, e.g., P.O.D. type.
//!  \tparam D The dimension of the array, i.e., the number of elements
//!    to be stored in the array.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t D> 
using point = math::vector<T,D>;

///
/// \function distance
///
template <typename T, size_t D>
T distance(const point<T, D> & a, const point<T, D> & b)
{
  T sum(0);
  for (size_t d(0); d < D; ++d) {
    sum += (a[d] - b[d])*(a[d] - b[d]);
  } // for

  return std::sqrt(sum);
} // distance

///
// \function midpoint
///
template <typename T, size_t D>
point<T, D> midpoint(const point<T, D> & a, const point<T, D> & b)
{
  return point<T, D>((a + b) / 2.0);
} // distance

///
// Compute the centroid of a list of points.
//
// \param[in] cell The cell to return the centroid for.
// \return a point that is the centroid.
///
template <template <typename...> class LIST, typename T, size_t D>
auto centroid(const LIST<point<T, D>> & vert_list)
{
  point<T, D> tmp(0.0);
  for (auto v : vert_list)
    tmp += v;
  tmp /= vert_list.size();
  return tmp;
} // centroid

template <typename T, size_t D>
auto centroid(std::initializer_list<point<T, D>> vert_list)
{
  point<T, D> tmp(0.0);
  for (auto v : vert_list)
    tmp += v;
  tmp /= vert_list.size();
  return tmp;
} // centroid

} // namespace
} // namespace
