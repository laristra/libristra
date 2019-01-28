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
#include <type_traits>

namespace ristra {
namespace utils {
namespace detail {

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

////////////////////////////////////////////////////////////////////////////////
//! \brief Helper type to check that T has operator[]
////////////////////////////////////////////////////////////////////////////////
template <class T, class Index, class = void>
struct has_subscript_operator_impl : std::false_type {
};

template <class T, class Index>
struct has_subscript_operator_impl<T, Index,
  std::void_t<decltype(std::declval<T>()[std::declval<Index>()])>>
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
  std::void_t<decltype(std::declval<T>()(std::declval<Args>()...))>, Args...>
  : std::true_type {
};

////////////////////////////////////////////////////////////////////////////////
//! \brief A helper type for checking if a particular type T is callable with
//! any signature--i.e. does it define operator().
//
//! \remark See https://stackoverflow.com/questions/15393938/
//! \remark Basic idea is, if the call operator is the same as Fallback's, then
//! T does not implemant a call operator.
//! \remark Updated a bit to use true_type / false_type, instead of the olde
//! school sizeof trick.
////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct is_callable {
 private:

  struct Fallback {
    void operator()();
  };
  struct Derived : T, Fallback {
  };

  template <typename U, U>
  struct Check;

  template <typename>
  static std::true_type test(...);

  template <typename C>
  static std::false_type test(Check<void (Fallback::*)(), &C::operator()> *);

 public:
  //! \brief True if T is callable.
  using result_type = decltype(test<Derived>(0));
  static const bool value = result_type::value ;
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
}

} // detail::
} // utils::
} // ristra::
