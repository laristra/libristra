// inputs_non_static_impl.h
// T. M. Kelley
// May 15, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

/** \file inputs_non_static_impl.h
 * Macros and types to support invoking functions and functors on
 * a set of types, absent argument-driven type deduction.
 *
 * These macros address the problem of invoking a templated function
 * or functor on each type in a set of types. Typically this is done
 * with a tuple of arguments (see flesci/utils/tuple_for_each). What if
 * that tuple is not available? For example, what if some of the types
 * involved are not default-constructible? In that case, we need to
 * use a slightly more circuitous route. In the end, it's a bit cleaner
 * and it's really not much extra work.
 *
 *
  */
#pragma once

#include <tuple>

/*
  apply_f_by_tuple(<func_name>) provides a pair of functions that
  will invoke <func_name> on every type of a tuple, assembling
  the results into an initializer list (well, that would be ideal, but
  right now it's not quite working that way.)

  The user must define:

  template <class T, size_t I>
  ret_t my_function{ ... }

  It must be templated on a class and an index. The index is there for
  convenience.

  The user will call

  <func_name>_by_tuple<type_tuple>();

  To use this, you need to provide the function named "<func_name>", and
  somewhere you need to invoke

  apply_f_by_tuple(<func_name>)

  It is modeled on this code:

  ///\brief Apply resolve_inputs to each type in a tuple.
  template <typename Tuple, std::size_t... Is>
  auto resolve_by_tuple_impl(std::index_sequence<Is...>) {
   using parm_list = param_list<Tuple>;
   auto l = {resolve_inputs_<typename parm_list::template type<Is> >()...};
   return l;
  } // resolve_by_tuple_impl

  template <typename Tuple>
  auto resolve_by_tuple(){
    constexpr size_t tsize(std::tuple_size<Tuple>::value);
    return resolve_by_tuple_impl<Tuple>(std::make_index_sequence<tsize>{});
  } // resolve_by_tuple

  Because resolve_by_tuple works only at the type level (there is no Tuple
  value to drive type deduction) we need to take the extra step of
  enumerating the types in the tuple. That's what the std::index_sequence
  does here.

  Note: if you get errors like:

  inputs_non_static_impl.h:72:61: error: expected ‘(’ before ‘>’ token
     99   auto l = {(func_name<typename parm_list::template type<Is> >())...};        \

  then the first thing to check is that you have the correct func_name!
*/

namespace ristra{
namespace detail{

/**\brief Helper class to grab the type of the Nth element of a tuple */
template <typename T> struct param_list {
  template <std::size_t N> using type = typename std::tuple_element<N, T>::type;
};

/**\brief Find the index of the first occurence of a type in a tuple.
 * cf. stackoverflow 18063451 */
template <class T, class Tuple>
struct tuple_index;

template <class T, class ...Ts>
struct tuple_index<T,std::tuple<T,Ts...>>{
  static constexpr size_t value = 0;
};

template <class T, class U, class ...Ts>
struct tuple_index<T,std::tuple<U,Ts...>>{
  static constexpr size_t value = 1 + tuple_index<T,std::tuple<Ts...>>::value;
};

} // detail::
} // ristra::


#define apply_f_by_tuple(func_name)                                     \
                                                                        \
template <typename Tuple, std::size_t... Is>                            \
inline                                                                  \
auto func_name##_tuple_impl(std::index_sequence<Is...>) {               \
 using parm_list = detail::param_list<Tuple>;                           \
 using return_type =                                                    \
  decltype(func_name<typename parm_list::template type<0>,0>());        \
 std::deque<return_type> d(                                             \
  {func_name<typename parm_list::template type<Is>,Is>()...});          \
 return std::move(d);                                                   \
}                                                                       \
                                                                        \
template <typename Tuple>                                               \
inline                                                                  \
auto func_name##_by_tuple() {                                           \
 constexpr size_t tsize(std::tuple_size<Tuple>::value);                 \
 return                                                                 \
   func_name##_tuple_impl<Tuple>(std::make_index_sequence<tsize>{});    \
}

/**\brief Apply a  */
#define apply_op_f_by_tuple(struct_name)                                \
                                                                        \
template <typename Tuple, typename ...Args, std::size_t... Is>          \
inline                                                                  \
auto struct_name##_tuple_impl(std::index_sequence<Is...>,               \
                              Args&&...args) {                          \
 using parm_list = detail::param_list<Tuple>;                           \
 using return_type =                                                    \
  decltype(struct_name<typename parm_list::template type<0>,0>()(       \
    std::forward<Args>(args)...));                                      \
 std::deque<return_type> d(                                             \
  {struct_name<typename parm_list::template type<Is>,Is>()(             \
    std::forward<Args>(args)...)...});                                  \
 return std::move(d);                                                   \
}                                                                       \
                                                                        \
template <typename Tuple, typename ...Args>                             \
inline                                                                  \
auto struct_name##_by_tuple(Args&&...args) {                            \
 constexpr size_t tsize(std::tuple_size<Tuple>::value);                 \
 return                                                                 \
   struct_name##_tuple_impl<Tuple>(std::make_index_sequence<tsize>{},   \
                                   std::forward<Args>(args)...);        \
}



#define apply_void_f_by_tuple(func_name)                                \
                                                                        \
template <typename Tuple, typename ...Args, std::size_t... Is>          \
inline                                                                  \
void func_name##_tuple_impl(std::index_sequence<Is...>,Args&&...args) { \
 using parm_list = detail::param_list<Tuple>;                           \
 auto d =                                                               \
   {(func_name<typename parm_list::template type<Is>,Is>(               \
        std::forward<Args>(args)... ),0)...};                               \
 return;                                                                \
}                                                                       \
                                                                        \
template <typename Tuple, typename ...Args>                              \
inline                                                                  \
void func_name##_by_tuple(Args && ...args) {                               \
 constexpr size_t tsize(std::tuple_size<Tuple>::value);                 \
 func_name##_tuple_impl<Tuple>(std::make_index_sequence<tsize>{},      \
                               std::forward<Args>(args)...);                 \
 return;                                                                \
}


// End of file
