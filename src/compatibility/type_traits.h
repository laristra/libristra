/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Stuff in C++'s type_traits library that is not available till C++17.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include <type_traits>

namespace ristra {
namespace compatibility {

////////////////////////////////////////////////////////////////////////////////
//! \brief A is_same helper type.  True if T and U are the same types.
//! \tparam T,U  The types to test if they are the same.
////////////////////////////////////////////////////////////////////////////////
template <class T, class U>
constexpr bool is_same_v = std::is_same<T, U>::value;

////////////////////////////////////////////////////////////////////////////////
//! \brief A is_arithmetic helper type.  True if T is an arithmetic type.
//! \tparam T  The type to test.
////////////////////////////////////////////////////////////////////////////////
template <class T>
constexpr bool is_arithmetic_v = std::is_arithmetic<T>::value;

////////////////////////////////////////////////////////////////////////////////
//! \brief A is_function helper type.  _Not_ true if T is a std::function.
//!
//! \tparam T  The type to test.
//! Note that std::is_function returns false for std::function, lambdas, and
//! classes with operator().
//! Cf. http://en.cppreference.com/w/cpp/types/is_function, also unit test.
////////////////////////////////////////////////////////////////////////////////
template <class T>
constexpr bool is_function_v = std::is_function<T>::value;

////////////////////////////////////////////////////////////////////////////////
//! \brief A is_integral helper type.  True if T is an integral type.
//! \tparam T  The type to test.
////////////////////////////////////////////////////////////////////////////////
template <class T>
constexpr bool is_integral_v = std::is_integral<T>::value;

} // namespace utils
} // namespace ristra
