/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some helper functions for template foo magic.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// user includes 
#include "detail/template_helpers_impl.h"
#include "../common/types.h"

// system includes
#include <functional>
#include <limits>

namespace flecsi {
namespace sp {
namespace utils {

////////////////////////////////////////////////////////////////////////////////
//! \brief The main interface to multiply arguments together.
//! \return The rusult of arg1*arg2*...
////////////////////////////////////////////////////////////////////////////////
template<typename... Args>
constexpr auto multiply(Args... args) 
{ return detail::multiply(args...); }



////////////////////////////////////////////////////////////////////////////////
//!  \brief select the appropriate counter type at compile time.
//!
//!  \tparam N The maximum dimension to be indexed.
////////////////////////////////////////////////////////////////////////////////
template< std::size_t N, bool >
struct select_counter;

//! \copydoc select_counter
//! \remark this version gets instantiated for 32bit indexing
template< std::size_t N >
struct select_counter<N,true> 
{
  using type = int;
};

//! \copydoc select_counter
//! \remark this version gets instantiated for large numbers
template< std::size_t N >
struct select_counter<N,false>
{
  using type = common::counter_t;
};

//! \brief a helper for selecting the appropriate counter
template< std::size_t N >
using select_counter_t = 
  typename select_counter<N, (N < std::numeric_limits<int>::max()) >::type;

////////////////////////////////////////////////////////////////////////////////
//! \brief statically fill an array with a constant value
////////////////////////////////////////////////////////////////////////////////
//! @{

template <std::size_t N>
struct fill {
  template <typename T, typename ...Tn>
  static constexpr auto apply(T v, Tn ...vs)
  {
    return fill<N - 1>::apply(v, v, vs...);
  }
};

template <>
struct fill<1> {
  template <typename T, typename ...Tn>
  static constexpr auto apply(T v, Tn ...vs)
  {
    return std::array<T, sizeof...(vs) + 1>{v, vs...};
  }

};

//! @}


////////////////////////////////////////////////////////////////////////////////
//! \brief This is the main interface to make_array.
//! \param [in] val  The value to fill the array with.
//! \tparam T The value_type of the array.
//! \tparam N The size of the array
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t N>
constexpr std::array<T, N> make_array(T val)
{
  return detail::make_array(val, std::make_index_sequence<N>());
}

////////////////////////////////////////////////////////////////////////////////
//! \brief A std::tie-like function using constant references.
//! \param [in] first,rest The values of the tuple to reference.
////////////////////////////////////////////////////////////////////////////////
template < typename T, typename... Ts >
std::tuple<T&, const Ts&...> ctie( T& first, const Ts&... rest )
{
  return std::make_tuple( std::ref(first), std::cref(rest)... );
}

////////////////////////////////////////////////////////////////////////////////
//! \brief This is a helper function to unpack a tuple and create references.
//! \remark This is the main interface
//! \tparam T  The tuple type
////////////////////////////////////////////////////////////////////////////////
template < typename T >
using reference_wrapper_t = typename detail::reference_wrapper<T>::type;


////////////////////////////////////////////////////////////////////////////////
//! \brief return an lvalue reference to val.
////////////////////////////////////////////////////////////////////////////////
template<typename T>
T &as_lvalue(T &&val) {
  return val;
}

} // namespace
} // namespace
} // namespace

