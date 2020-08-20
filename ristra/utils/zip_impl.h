/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
///
/// \brief Provide a zip-like iterator for range-based fors.
///
/// This lets us do something like: for (auto i : zip(a, b, c) )
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <cstddef>
#include <iterator>
#include <tuple>

namespace ristra {
namespace utils {
namespace detail {

////////////////////////////////////////////////////////////////////////////////
//! \brief helper for tuple_subset and tuple_tail 
//!
//! This is essentially a std::integer_sequence, whith an ability to append
//! indices statically at compile time.
//!
//! \see http://stackoverflow.com/questions/8569567/get-part-of-stdtuple
////////////////////////////////////////////////////////////////////////////////
template <std::size_t... n>
struct ct_integers_list {
  template <size_t m>
  struct push_back
  {
    using type = ct_integers_list<n..., m>;
  };
};

////////////////////////////////////////////////////////////////////////////////
//! \brief A compile time type that provides functionality like std::iota.
////////////////////////////////////////////////////////////////////////////////
//! @{
template <std::size_t max>
struct ct_iota_1
{
  using type = typename ct_iota_1<max-1>::type::template push_back<max>::type;
};

//! \remark This ends the recursive expansion.
template <>
struct ct_iota_1<0>
{
  using type = ct_integers_list<>;
};
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief Return a subset of a tuple.
//! \param [in] tpl  The tuple to index.
//! \param [in] ct_integers_list  The compile-time list of indices to extract.
//! \tparam Tuple The tuple type.
//! \tparam indices The indices of the tuple to extract.
//! \return The subset of the original tuple \a tpl.
////////////////////////////////////////////////////////////////////////////////
template <std::size_t... indices, typename Tuple>
decltype(auto) tuple_subset(Tuple&& tpl, ct_integers_list<indices...>)
{
  return std::make_tuple(std::get<indices>(std::forward<Tuple>(tpl))...);
  // this means:
  //   make_tuple(get<indices[0]>(tpl), get<indices[1]>(tpl), ...)
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Return a the tail of a tuple.
//! \param [in] tpl  The tuple to index.
//! \param [in] ct_integers_list  The compile-time list of indices to extract.
//! \tparam Tuple The tuple type.
//! \tparam indices The indices of the tuple to extract.
//! \return The subset of the original tuple \a tpl.
////////////////////////////////////////////////////////////////////////////////
template <typename Head, typename... Tail>
decltype(auto) tuple_tail(const std::tuple<Head, Tail...>& tpl)
{
  return tuple_subset(tpl, typename ct_iota_1<sizeof...(Tail)>::type());
  // this means:
  //   tuple_subset<1, 2, 3, ..., sizeof...(Tail)-1>(tpl, ..)
}

////////////////////////////////////////////////////////////////////////////////
//! \brief increment every element in a tuple (that is referenced)
//! \tparam Tp  The tuple types.
//! \param [in] t  The tuple to increment.
////////////////////////////////////////////////////////////////////////////////
//! @{
template<std::size_t I = 0, typename... Tp>
typename std::enable_if<I == sizeof...(Tp), void>::type
increment(std::tuple<Tp...>& t)
{ }

template<std::size_t I = 0, typename... Tp>
typename std::enable_if<(I < sizeof...(Tp)), void>::type
increment(std::tuple<Tp...>& t)
{
  std::get<I>(t)++ ;
  increment<I + 1, Tp...>(t);
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief check inequality of a tuple
//! \param [in] t1,t2 The tuples to check inequality.
//! \tparam T1,T2 The tuple types.
//! \return true if the \a t1 and \a t2 are not equal.
////////////////////////////////////////////////////////////////////////////////
//! @{
template<typename T1>
bool not_equal_tuples( const std::tuple<T1>& t1,  const std::tuple<T1>& t2 )
{
  return (std::get<0>(t1) != std::get<0>(t2));
}

template<typename T1, typename... Ts>
std::enable_if_t<(sizeof...(Ts) > 0), bool> not_equal_tuples( 
    const std::tuple<T1, Ts...>& t1,  
    const std::tuple<T1, Ts...>& t2 )
{
  return 
    (std::get<0>(t1) != std::get<0>(t2)) && 
    not_equal_tuples( tuple_tail(t1), tuple_tail(t2) );
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief check equality of a tuple
//! \param [in] t1,t2 The tuples to check equality.
//! \tparam T1,T2 The tuple types.
//! \return true if the \a t1 and \a t2 are equal.
////////////////////////////////////////////////////////////////////////////////
//! @{
template<typename T1>
bool equal_tuples( const std::tuple<T1>& t1,  const std::tuple<T1>& t2 )
{
  return (std::get<0>(t1) == std::get<0>(t2));
}

template<typename T1, typename... Ts>
std::enable_if_t<(sizeof...(Ts) > 0), bool> equal_tuples( 
    const std::tuple<T1, Ts...>& t1,  
    const std::tuple<T1, Ts...>& t2 )
{
  return 
    (std::get<0>(t1) == std::get<0>(t2)) && 
    equal_tuples( tuple_tail(t1), tuple_tail(t2) );
}
//! @}

////////////////////////////////////////////////////////////////////////////////
//! \brief dereference a subset of elements of a tuple (dereferencing the 
//!        iterators)
//! \param [in] t1 The tuple to dereference
//! \param [in] ct_integers_list  The compile list of indidces
//! \return A tuple of dereferenced objects constructed from \t1 
////////////////////////////////////////////////////////////////////////////////
template <std::size_t... indices, typename Tuple>
decltype(auto) dereference_subset(Tuple& tpl, ct_integers_list<indices...>)
{
  return std::tie(*std::get<indices-1>(tpl)...);
}

////////////////////////////////////////////////////////////////////////////////
//! \brief dereference every element of a tuple  (applying operator* to 
//!        each element, and returning the tuple)
//! \param [in] t1 The tuple to dereference
//! \return A tuple of dereferenced objects constructed from \t1 
////////////////////////////////////////////////////////////////////////////////
template<typename... Ts>
decltype(auto) dereference_tuple(std::tuple<Ts...>& t1)
{
  return dereference_subset( t1, typename ct_iota_1<sizeof...(Ts)>::type());
}


////////////////////////////////////////////////////////////////////////////////
//! \brief a struct to get the value type of a referenced or unreferenced object
////////////////////////////////////////////////////////////////////////////////
//! @{
template <class T, class Enable = void>
struct value_type
{ };

//! \remark This version gets used if \a T is not a reference
template <class T>
struct value_type< 
  T, 
  typename std::enable_if< !std::is_reference<T>::value >::type 
>
{
  // use this to use by value, but i dont like that
  // using type = typename T::value_type;

  // always use references
  using type = typename T::value_type&;
};

//! \remark This version gets used if \a T is a reference
template <class T>
struct value_type< 
  T, 
  typename std::enable_if< std::is_reference<T>::value >::type 
>
{
  using type =  typename std::remove_reference_t<T>::value_type&;
};

//! \brief Converts to the resulting referenced value type
template< class T >
using value_type_t = typename value_type<T>::type;
//! @}


////////////////////////////////////////////////////////////////////////////////
//! \brief the zipper class with iterator
//! \tparam T1,Ts  The types to zip together.
////////////////////////////////////////////////////////////////////////////////
template< typename T1, typename... Ts >
class zipper
{
public:

  class iterator : std::iterator< std::forward_iterator_tag, 
                                  std::tuple<value_type_t<T1>, value_type_t<Ts>...> >
  {
  protected:
    std::tuple<typename std::remove_reference_t<T1>::iterator, 
               typename std::remove_reference_t<Ts>::iterator...> current;
  public:

    explicit iterator(  typename std::remove_reference_t<T1>::iterator s1, 
                        typename std::remove_reference_t<Ts>::iterator... s2 ) : 
      current(s1, s2...) {};

    iterator( const iterator& rhs ) :  current(rhs.current) {};

    auto & operator++() {
      increment(current);
      return *this;
    }

    auto operator++(int) {
      auto a = *this;
      increment(current);
      return a;
    }

    bool operator!=( const iterator& rhs ) {
      return not_equal_tuples(current, rhs.current);
    }

    bool operator==( const iterator& rhs ) {
      return equal_tuples(current, rhs.current);
    }

    typename iterator::value_type operator*() {
      return dereference_tuple(current);
    }
  };


  zipper( T1& a, Ts&... b):
    begin_( a.begin(), (b.begin())...), 
    end_( a.end(), (b.end())...) {};

  zipper(const zipper<T1, Ts...>& a) :
    begin_( a.begin_ ), 
    end_( a.end_ ) {};

  template<typename U1, typename... Us>
  auto & operator=(const zipper<U1, Us...>& rhs) {
    begin_ = rhs.begin_;
    end_ = rhs.end_;
    return *this;
  }

  auto& begin() 
  { return begin_; }

  auto& end() 
  { return end_; }



  iterator begin_;
  iterator end_;
};

} // namespace detail
} // namespace
} // namespace
