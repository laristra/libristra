/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2017 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utilities to extend C++'s type_traits library.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// user includes
#include "flecsi-sp/utils/detail/type_traits_impl.h"

// system inculdes
#include <iterator>
#include <type_traits>
#include <utility>

namespace flecsi {
namespace sp {
namespace utils {


////////////////////////////////////////////////////////////////////////////////
// BEGIN Stuff not available till C++17
////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////
//! \brief A is_same helper type.  True if T and U are the same types.
//! \tparam T,U  The types to test if they are the same.
////////////////////////////////////////////////////////////////////////////////
template< class T, class U >
constexpr bool is_same_v = std::is_same<T, U>::value;


////////////////////////////////////////////////////////////////////////////////
//! \brief A is_arithmetic helper type.  True if T is an arithmetic type.
//! \tparam T  The type to test.
////////////////////////////////////////////////////////////////////////////////
template< class T >
constexpr bool is_arithmetic_v = std::is_arithmetic<T>::value;

////////////////////////////////////////////////////////////////////////////////
//! \brief A is_function helper type.  True if T is a std::function.
//! \tparam T  The type to test.
////////////////////////////////////////////////////////////////////////////////
template< class T >
constexpr bool is_function_v = std::is_function<T>::value;


////////////////////////////////////////////////////////////////////////////////
//! \brief A is_integral helper type.  True if T is an integral type.
//! \tparam T  The type to test.
////////////////////////////////////////////////////////////////////////////////
template< class T >
constexpr bool is_integral_v = std::is_integral<T>::value;


////////////////////////////////////////////////////////////////////////////////
// END Stuff not available till C++17
////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////
//! \brief Test to see if all variadic template arguments Ts are of type Target.
////////////////////////////////////////////////////////////////////////////////
template<typename Target, typename... Ts>
using are_type_t = detail::and_< 
  std::is_same< std::decay_t<Ts>, std::decay_t<Target> >... >;



////////////////////////////////////////////////////////////////////////////////
//! \brief Check if a particular type T is an iterator.
////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct is_iterator {
  //! \brief This function will get always get instantiated.
  static char test(...);
  //! \brief Use SFINAE to create this function if T is an iterator.
  template <typename U,
            typename=typename std::iterator_traits<U>::difference_type,
            typename=typename std::iterator_traits<U>::pointer,
            typename=typename std::iterator_traits<U>::reference,
            typename=typename std::iterator_traits<U>::value_type,
            typename=typename std::iterator_traits<U>::iterator_category
  > static long test(U&&);
  //! \breif True if T is an iterator and test(U) function exists.
  constexpr static bool value = std::is_same<decltype(test(std::declval<T>())),long>::value;
};

//! \brief Equal to true if T is an iterator.
template< typename T >
constexpr bool is_iterator_v = is_iterator<T>::value;


////////////////////////////////////////////////////////////////////////////////
//! \brief Check if a particular type T is callable.
////////////////////////////////////////////////////////////////////////////////
template<typename T>
struct is_callable : std::conditional<
  std::is_class<T>::value,
  detail::is_callable<T>,
  std::false_type 
>::type
{ };

//! \brief Equal to true if T is callable.
template< typename T >
constexpr bool is_callable_v = is_callable<T>::value;



////////////////////////////////////////////////////////////////////////////////
//! \brief Check if a particular type T is a container.
//! \remark If T is not, this version is instantiated.
//! \remark This version adheres to the strict requirements of an STL container.
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename _ = void>
struct is_container : std::false_type {};

//! \brief Check if a particular type T is a container.
//! \remark If T is, this version is instantiated.
//! \remark This version adheres to the strict requirements of an STL container.
template<typename T>
struct is_container<
  T,
  std::conditional_t<
    false,
    detail::is_container<
      typename T::value_type,
      typename T::size_type,
      typename T::allocator_type,
      typename T::iterator,
      typename T::const_iterator,
      decltype(std::declval<T>().size()),
      decltype(std::declval<T>().begin()),
      decltype(std::declval<T>().end()),
      decltype(std::declval<T>().cbegin()),
      decltype(std::declval<T>().cend()),
      decltype(std::declval<T>().data())
    >,
    void
  >
> : public std::true_type {};

//! \brief Equal to true if T is a container.
//! \remark This version adheres to the strict requirements of an STL container.
template< typename T >
constexpr bool is_container_v = is_container<T>::value;


////////////////////////////////////////////////////////////////////////////////
/// \brief A Helper to identify if this is a container
//! \remark If T is, this version is instantiated.
//! \remark This version uses to a reduced set of requirements for a container.
////////////////////////////////////////////////////////////////////////////////
template<typename T, typename _ = void>
struct is_minimal_container : std::false_type {};

/// \brief A Helper to identify if this is a container
//! \remark If T is, this version is instantiated.
//! \remark This version uses to a reduced set of requirements for a container.
template<typename T>
struct is_minimal_container<
  T,
  std::conditional_t<
    false,
    is_container<
      decltype(std::declval<T>().size()),
      decltype(std::declval<T>().data())
    >,
    void
  >
> : public std::true_type {};

//! \brief Equal to true if T is a container.
//! \remark This version uses to a reduced set of requirements for a container.
template< typename T >
constexpr bool is_minimal_container_v = is_minimal_container<T>::value;


////////////////////////////////////////////////////////////////////////////////    
/// \brief A helper to identify if all types Ts are integral.
//! \remark If they are not, this version is instantiated.
////////////////////////////////////////////////////////////////////////////////    
template <typename... Ts>
class are_integral : public std::integral_constant<bool, true>
{};

/// \brief A helper to identify if all types Ts are integral.
//! \remark If they are, this version is instantiated.
template <typename T, typename... Ts>
class are_integral<T, Ts...>
  : public std::integral_constant <
      bool,
      std::is_integral<T>::value && are_integral<Ts...>::value
    >
{};

//! Equal to true if Ts are all integral types.
template< typename... Ts >
constexpr bool are_integral_v = are_integral<Ts...>::value;



////////////////////////////////////////////////////////////////////////////////
//! \brief Extract the extents from an array of type T.
////////////////////////////////////////////////////////////////////////////////
template< typename T >
constexpr auto & extract_extents() 
{
  using Indices = std::make_index_sequence< std::rank<T>::value >;
  return detail::extract_extents_helper< T >( Indices{} );
}


////////////////////////////////////////////////////////////////////////////////
//! \brief A special version of decay that allows the use of references
//! \see cppreference.com
//! \remark This is the general template version.
////////////////////////////////////////////////////////////////////////////////
template <class T>
struct special_decay
{
  using type = typename std::decay<T>::type;
};

//! \brief A special version of decay that allows the use of references
//! \see cppreference.com
//! \remark This is the specialized version for references.
template <class T>
struct special_decay<std::reference_wrapper<T>>
{
  using type = T&;
};

//! \brief Converts to a decayed reference to an object of type T.
template <class T>
using special_decay_t = typename special_decay<T>::type;

} // namespace
} // namespace
} // namespace

