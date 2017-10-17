/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utilities to extend C++'s type_traits library.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <utility>

namespace ristra
{
namespace detail
{
////////////////////////////////////////////////////////////////////////////////
//! \brief Combine conditions.
//! \remark End the template expansion.
////////////////////////////////////////////////////////////////////////////////
template <typename... Conds>
struct and_ : std::true_type {
};

//! \brief Combine conditions.
//! \remark Main template expansion function.
template <typename Cond, typename... Conds>
struct and_<Cond, Conds...>
  : std::conditional<Cond::value, and_<Conds...>, std::false_type>::type {
};

template <class...>
using ignored_t = void;

////////////////////////////////////////////////////////////////////////////////
//! \brief Helper type to check that T has operator[]
////////////////////////////////////////////////////////////////////////////////
template <class T, class Index, class = void>
struct has_subscript_operator_impl : std::false_type {
};

template <class T, class Index>
struct has_subscript_operator_impl<T, Index,
  ignored_t<decltype(std::declval<T>()[std::declval<Index>()])>>
  : std::true_type {
};

////////////////////////////////////////////////////////////////////////////////
//! \brief Helper type to check that T is callable with Args.
////////////////////////////////////////////////////////////////////////////////
template <class T, class, class... Args>
struct has_call_operator_impl : std::false_type {
};

template <class T, class... Args>
struct has_call_operator_impl<T,
  ignored_t<decltype(std::declval<T>()(std::declval<Args>()...))>, Args...>
  : std::true_type {
};

////////////////////////////////////////////////////////////////////////////////
//! \brief A helper type for checking if a particular type T is callable.
////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct is_callable {
 private:
  typedef char (&yes)[1];
  typedef char (&no)[2];

  struct Fallback {
    void operator()();
  };
  struct Derived : T, Fallback {
  };

  template <typename U, U>
  struct Check;

  template <typename>
  static yes test(...);

  template <typename C>
  static no test(Check<void (Fallback::*)(), &C::operator()> *);

 public:
  //! \brief True if T is callable.
  static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

////////////////////////////////////////////////////////////////////////////////
//! \brief A helper type to check if a particular type is a container.
////////////////////////////////////////////////////////////////////////////////
template <typename... Ts>
struct is_container {
};

////////////////////////////////////////////////////////////////////////////////
//! \brief A helper to extract the extents from an array.
////////////////////////////////////////////////////////////////////////////////
template <typename T, std::size_t... I>
constexpr auto extract_extents_helper(std::index_sequence<I...>)
{
  constexpr std::size_t extents[std::rank<T>::value] = {
    std::extent<T, I>::value...};
  return extents;
};

} // detail::
} // ristra::
