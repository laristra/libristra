/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some helper functions for template foo magic.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <array>

namespace flecsi {
namespace sp {
namespace utils {
namespace detail {


////////////////////////////////////////////////////////////////////////////////
//! \brief Helpers to statically multiply arguments together
////////////////////////////////////////////////////////////////////////////////
//! @{
//! \brief return 1 for the final multiplcation
constexpr std::size_t multiply() 
{ return 1; }

//! \brief main implementation for multiplication
template<typename Arg, typename... Args>
constexpr auto multiply(Arg first, Args... rest) 
{ return first * multiply(rest...); }
//! @}



////////////////////////////////////////////////////////////////////////////////
//! \brief statically make an array with a constant value
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t...Is>
constexpr std::array<T, sizeof...(Is)> make_array(T val, std::index_sequence<Is...>)
{
  return {(static_cast<void>(Is), val)...};
}

////////////////////////////////////////////////////////////////////////////////
//! \brief A type traits type struct used to unpack a tuple type, and repack it 
//!        using references.
////////////////////////////////////////////////////////////////////////////////
//! @{

//! \brief Unpack a tuple and create a tuple of references to each element.
//! \tparam T  The tuple type
//! \remark This is the empty struct
template < typename T >
struct reference_wrapper {};

//! \brief Unpack a tuple and create a tuple of references to each element.
//! \tparam Tuple  The tuple type
//! \remark This is the tuple implementation
template < template<typename...> class Tuple, typename... Args >
struct reference_wrapper < Tuple<Args...> >
{
  using type = Tuple<Args&...>;
};

//! @}

} // namespace 
} // namespace 
} // namespace
} // namespace

