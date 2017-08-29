/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016-7 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Lua result type.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef HAVE_LUA

#ifndef LUA_ACCESS_H_INCLUDED
#error "Use top-level entry point, lua_access.h!!"
#endif

#include "ristra/dbc.h"
#include "ristra/errors.h"

namespace ristra {
namespace detail{

////////////////////////////////////////////////////////////////////////////////
/// \brief This class stores a reference to a lua value.
/// The class is used to convert the refered lua value to a desired type.  It is
/// is the root of the implementation.
////////////////////////////////////////////////////////////////////////////////
class lua_result_t : public lua_base_t {

  /// \brief The name of the object.
  std::string name_;
  /// \brief A reference to the lua value in the LUA_REGISTRYINDEX table.
  std::vector<lua_ref_t> refs_;
  /// \brief The size of the object on the stack
  std::size_t size_ = 0;

  /// \defgroup get_results get_results
  /// \brief These templates are used to extract multiple results as tuples.
  /// \{

  /// \brief Final templated function to end the recursion.
  /// \tparam Tup The tuple type the data gets stored as.
  /// \tparam I The static index of the tuple.
  /// \param [in,out] tup  The tuple to store the lua results in.
  template< typename Tup, int I >
  void get_results( Tup & tup ) const
  {}

  /// \brief Main recursive function to set each value of the tuple.
  /// \tparam Tup The tuple type the data gets stored as.
  /// \tparam I The static index of the tuple.
  /// \tparam Arg1,Args  The requested argument types.
  /// \param [in,out] tup  The tuple to store the lua results in.
  template<
    typename Tup, int I, typename Arg1, typename... Args
  >
  void get_results( Tup & tup ) const
  {
    std::get<I>(tup) = lua_value<Arg1>::get( state() );
    // recursively extract tuple
    get_results<Tup,I+1,Args...>( tup );
  }
  /// /}

  /// \defgroup push_args push_args
  /// \brief These templates are used to push function arguments on the stack.
  /// \{

  /// \brief Final templated function to end the recursion.
  void push_args() const
  {}

  /// \brief The main recursive function.
  /// \tparam Arg,Args  The function argument types.
  /// \param [in]  arg,args  The values of the function arguments.
  template< typename Arg, typename... Args >
  void push_args( Arg&& arg, Args&&... args ) const
  {
    // grow the stack
    check_stack(1);
    // chop off an argument and push it
    lua_push( state(), std::forward<Arg>(arg) );
    // set the remaining arguments
    push_args(std::forward<Args>(args)...);
  }
  /// /}

  /// \brief Check the stack to make sure it can be expanded.
  /// \param [in] extra The desired size to grow the stack by.
  void check_stack(int extra) const
  {
    auto s = state();
    auto ret = lua_checkstack(s, extra);
    if ( !ret ) {
      std::ostringstream ss;
      ss << "Cannot grow stack " << extra << " slots operating on element \""
         << name_ << "\"." << std::endl << "Current stack size is "
         << lua_gettop(s) << ".";
      raise_runtime_error(ss.str());
    }
  }

  void check_nil(const std::string & name) const
  {
    if ( lua_isnil(state(), -1) ) {
      print_last_row();
      raise_runtime_error("\"" + name + "\" does not exist.");
    }
  }

  void check_table(const std::string & name) const
  {
    check_nil(name);
    if ( !lua_istable(state(), -1) ) {
      print_last_row();
      raise_runtime_error("\"" + name + "\" is not a table.");
    }
  }

  /// \brief Check that a result is valid.
  /// \parm [in] name  The name of the object we are checking.
  void check_result(const std::string & name) const
  {
    if (lua_isnil(state(), -1)) {
      print_last_row();
      raise_runtime_error("\"" + name + "\" returned nil.");
    }
  }

  /// \brief Check that a result is a function.
  /// \parm [in] name  The name of the object we are checking.
  void check_function(const std::string & name) const
  {
    check_nil(name);
    if ( !lua_isfunction(state(), -1) ) {
      print_last_row();
      raise_runtime_error("\"" + name + "\" is not a function.");
    }
  }

  /// \brief Push the last value onto the stack.
  /// \remark The stack references are collected in reverse order.
  void push_last() const
  {
    check_stack(1);
    refs_.back().push();
  }

  /// \brief Push all referred values onto the stack.
  /// \remark The stack references are collected in reverse order.
  void push_all() const
  {
    // make sure the stack can handle this
    check_stack(refs_.size());
    // push everything onto the stack in reverse order
    for ( auto && r : refs_ ) std::forward<decltype(r)>(r).push();
  }

public:

  /// \brief No default constructor.
  lua_result_t() = delete;

  /// \brief This is the main constructor with a single reference.
  /// \param [in] state  The lua state pointer.
  /// \param [in] name  The name of the object.
  /// \param [in] ref  A reference to the last value popped off the stack.
  /// \param [in] size  The size of the object on the stack.
  lua_result_t(
    const lua_state_ptr_t & state,
    const std::string & name,
    lua_ref_t && ref,
    std::size_t size
  ) : lua_base_t(state), name_(name), refs_({std::move(ref)}), size_(size)
  {}

  /// \brief This is the main constructor with a multiple references.
  /// \param [in] state  The lua state pointer.
  /// \param [in] name  The name of the object.
  /// \param [in] refs  A references to the last set of values popped off the
  ///                   stack.
  lua_result_t(
    const lua_state_ptr_t & state,
    const std::string & name,
    std::vector<lua_ref_t> && refs
  ) : lua_base_t(state), name_(name), refs_(std::move(refs)),
      size_(refs_.size())
  {}

  /// \brief Return true if all references are nil.
  bool empty() const
  {
    for ( const auto & r : refs_ )
      if (!r.empty()) return false;
    return true;
  }

  /// \brief Return the name of the object.
  const auto & name() const
  {
    return name_;
  }

  /// \brief Return the size of the table.
  std::size_t size() const
  {
    return size_;
  }

  /// \brief Explicit type conversion operators for single values.
  /// \tparam T The type to convert to.
  /// \return The typecast value.
  template< typename T >
  explicit operator T() const {
    if ( refs_.size() != 1 ){
      HERE("");
      raise_runtime_error(
        "Expecting 1 result, stack has " + std::to_string(refs_.size()));
    }
    push_last();
    return lua_value<T>::get(state());
  }

  /* Note: clang 4.0 does not call this version from a static_cast.
   * Is that an error? Undefined behavior? Not sure... Anyhoo, that's
   * why there's to_tuple instead.
  */

  /// \brief Explicit type conversion operators for tuples.
  /// \tparam Args The element types of the tuple.
  /// \return The typecast tuple of values.
  template< typename...Args >
  explicit operator std::tuple<Args...>() const {
    constexpr int N = sizeof...(Args);
    using Tup = std::tuple<Args...>;
    if ( refs_.size() != N )
      raise_runtime_error("Expecting " + std::to_string(N) +
        " results, stack has " + std::to_string(refs_.size()));
    push_all();
    Tup tup;
    get_results<Tup,0,Args...>(tup);
    return tup;
  }

  /// \brief Explicit conversion for tuples.
  /// \tparam Args The element types of the tuple.
  /// \return The tuple of values.
  template <typename...Args>
  std::tuple<Args...> to_tuple() const {
    constexpr int N = sizeof...(Args);
    using Tup = std::tuple<Args...>;
    if ( refs_.size() != N ){
      raise_runtime_error("Expecting " + std::to_string(N) +
        " results, stack has " + std::to_string(refs_.size()));
    }
    push_all();
    Tup tup;
    get_results<Tup,0,Args...>(tup);
    return tup;
  }

  /// \brief Explicit type conversion operators for single values.
  /// \tparam T The type to convert to.
  /// \return The typecast value.
  template< typename T >
  T as() const {
    return static_cast<T>(*this);
  }

  /// \brief Explicit type conversion operators for tuples.
  /// \tparam T1, T2, Args The element types of the tuple.
  /// \return The typecast tuple of values.
  template< typename T1, typename T2, typename...Ts >
  auto as() const {
    return to_tuple<T1,T2,Ts...>();
  }

  /// \brief Evaluate a lua function.
  /// \tparam Args The function argument types.
  /// \param [in] args The argument types.
  /// \return A new lua_result_t with a reference to the result of the function
  ///         call.
  template < typename...Args >
  lua_result_t operator()(Args&&...args) const
  {
    auto s = state();
    // get the current stack position ( the function and arguments will get
    // deleted from the stack after the function call )
    auto pos0 = lua_gettop(s);
    // push the function onto the stack
    check_stack(1);
    push_last();
    // now make sure its a function
    check_function(name_);
    // add the arguments
    push_args(std::forward<Args>(args)...);

    // keep track of the arguments
    auto pos1 = lua_gettop(s);
    std::stringstream args_ss;
    args_ss << "(";
    for ( auto p = pos0+1; p<=pos1; ++p ) {
      auto t = lua_type(s, p);
      args_ss << lua_typename(s, t);
      if (p<pos1) args_ss << ",";
    }
    args_ss << ")";
    // call the function

    auto ret = lua_pcall(s, sizeof...(args), LUA_MULTRET, 0);
    if (ret) {
      print_last_row();
      raise_runtime_error("Problem calling \"" + name_ + "\".");
    }

    // make sure the result is non nill
    check_result(name_);
    // figure out how much the stack grew
    pos1 = lua_gettop(s);
    auto num_results = pos1 - pos0;
    GreaterEqual(num_results,0);

    // because there could be multiple results, get a reference to each one
    std::vector<lua_ref_t> ref_list;
    ref_list.reserve( num_results );
    for (int i = 0; i < num_results; ++i) {
      ref_list.emplace_back( std::move(make_lua_ref(state_)) );
    }

    // get the result
    return { state_, name_+args_ss.str(), std::move(ref_list) };
  }

  /// \brief Get the lua value in the table given a key.
  /// \param [in] key  The key to search for.
  /// \return A new lua_result_t with a reference to the result of the table
  ///         lookup.
  lua_result_t operator[]( const std::string & key ) const &
  {
    auto s = state();
    auto new_name = name_+".[\""+key+"\"]";
    // push the table onto the stack
    push_last();
    // make sure we are accessing a table
    check_table(name_);
    // push the key onto the stack
    check_stack(1);
    lua_pushlstring(s, key.c_str(), key.size());
    // now get the table value, the key gets pushed from the stack
    lua_rawget(s, -2);
    // get the size of the object
    auto len = lua_rawlen(s, -1);
    // get a reference to the result, and pop the table from the stack
    auto ref = make_lua_ref(state_);
    lua_pop(s, -1);
    // return the global object with a pointer to a location in the stack
    return { state_, new_name, std::move(ref), len };
  }

  /// \brief Get the lua value in the table given an index.
  /// \param [in] n  The index to access.
  /// \return A new lua_result_t with a reference to the result of the table
  ///         lookup.
  lua_result_t operator[]( int n ) const &
  {
    auto s = state();
    auto new_name = name_+"["+std::to_string(n)+"]";
    // push the table onto the stack
    push_last();
    // make sure we are accessing a table
    check_table(name_);
    // now get the table value, the key gets pushed from the stack
    lua_rawgeti(s, -1, n);
    // get the size of the object
    auto len = lua_rawlen(s, -1);
    // get a reference to the result, and pop the table from the stack
    auto ref = make_lua_ref(state_);
    lua_pop(s, -1);
    // return the global object with a pointer to a location in the stack
    return { state_, new_name, std::move(ref), len };
  }

}; // lua_result_t

using lua_result_uptr_t = std::unique_ptr<lua_result_t>;

} // detail::
} // ristra::

#endif // HAVE_LUA

