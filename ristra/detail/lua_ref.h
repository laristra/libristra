/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016-7 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Access to Lua interpreter.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef HAVE_LUA

#ifndef LUA_ACCESS_H_INCLUDED
#error "Use top-level entry point, lua_access.h!!"
#endif

#include "ristra/errors.h"

#include <vector>

namespace ristra {
namespace detail{

////////////////////////////////////////////////////////////////////////////////
/// \defgroup lua_push lua_push
/// \brief Functions to push values onto the lua stack.
////////////////////////////////////////////////////////////////////////////////
/// \{

/// \brief Push an integer onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] i  The integer to push.
inline size_t lua_push(lua_State * s, int i)
{
  lua_pushinteger( s, i );
  return 1;
}

/// \brief Push a long long onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] i  The long long to push.
inline size_t lua_push(lua_State * s, long long i)
{
  lua_pushinteger( s, i );
  return 1;
}

/// \brief Push a float onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] x  The float to push.
inline size_t lua_push(lua_State * s, float x)
{
  lua_pushnumber( s, x );
  return 1;
}

/// \brief Push a double onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] x  The double to push.
inline size_t lua_push(lua_State * s, double x)
{
  lua_pushnumber( s, x );
  return 1;
}

/// \brief Push a boolean onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] b  The boolean to push.
inline size_t lua_push(lua_State * s, bool b)
{
  lua_pushboolean( s, b );
  return 1;
}

/// \brief Push a character array onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] str  The character array to push.
inline size_t lua_push(lua_State * s, const char * str)
{
  lua_pushstring( s, str );
  return 1;
}

/// \brief Push a std::string onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] str  The string to push.
inline size_t lua_push(lua_State * s, const std::string & str)
{
  lua_pushlstring( s, str.c_str(), str.size() );
  return 1;
}
/// \brief Push a std::array onto the stack.
/// \param [in] s  The lua state to push a value to.
/// \param [in] str  The array to push.
template <size_t N>
inline size_t lua_push(lua_State * s, const std::array<double,N> & arr)
{
  // Caller always checks for 1, we must check for the rest
  auto ret = lua_checkstack(s, N-1);
  if ( !ret ) {
    std::ostringstream ss;
    ss << "Cannot grow stack " << (N - 1) << " slots operating on element \""
       << "\"." << std::endl
       << "Current stack size is " << lua_gettop(s) << ".";
    throw_runtime_error(ss.str());
  }
  // push each element of the array
  for(size_t i = 0; i < N; ++i){
    lua_push( s, arr[i]);
  }
  return N;
}
/// \}

////////////////////////////////////////////////////////////////////////////////
/// \brief A class to keep track of a lua reference.
////////////////////////////////////////////////////////////////////////////////
class lua_ref_t : public lua_base_t {

  /// \brief The reference is stored as a shared_ptr to an int.
  /// A shared pointer is used so that the reference isn't deleted until
  /// all associated objects are destroyed.  Multiple copies of a single
  /// reference may exist.
  std::shared_ptr<int> ref_;

  /// \brief Also store the type id of the object we are referencing
  int type_ = LUA_TNONE;

public:

  /// Delete the default destructor.
  lua_ref_t() = delete;

  /// \brief The main constructor.
  /// References are created in LUA_REGISTRYINDEX table.
  /// \param [in] state  A pointer to a lua state.
  /// \param [in] ref  The lua reference key.
  lua_ref_t ( const lua_state_ptr_t & state, int ref, int type )
    : lua_base_t(state),
      ref_(
        new int{ref},
        [s=state](int * r)
        { luaL_unref(s.get(), LUA_REGISTRYINDEX, *r); }
      ),
      type_(type)
  {}

  /// \brief Constructor to create an empty reference.
  lua_ref_t( const lua_state_ptr_t & state )
    : lua_ref_t(state, LUA_REFNIL, LUA_TNONE)
  {}

  /// \brief Push the refered value onto the stack.
  void push() const
  {
    lua_rawgeti(state(), LUA_REGISTRYINDEX, *ref_);
  }

  /// \brief return true if the pointed reference is null
  bool empty() const
  {
    return (*ref_ == LUA_REFNIL || *ref_ == LUA_NOREF);
  }

}; // class lua_ref_t

/// \brief Create a lua reference to the last value on the stack.
/// \param [in] state A lua state pointer.
/// \return A new lua_ref_t object.
inline lua_ref_t make_lua_ref(const lua_state_ptr_t & state)
{
  auto s = state.get();
  return { state, luaL_ref(s, LUA_REGISTRYINDEX), lua_type(s, -1) };
}

} // detail::
} // ristra::

#endif // HAVE_LUA

