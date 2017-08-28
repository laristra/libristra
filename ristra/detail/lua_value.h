/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef HAVE_LUA

#ifndef LUA_ACCESS_H_INCLUDED
#error "Use top-level entry point, lua_access.h!!"
#endif

// user includes
#include "ristra/errors.h"
#include "ristra/detail/lua_utils.h"

// use lua
extern "C" {
  #include <lua.h>
  #include <lauxlib.h>
}

#include <string>
#include <type_traits>

namespace ristra {

////////////////////////////////////////////////////////////////////////////////
/// \defgroup lua_value lua_value
/// \brief A struct to extract and typecast values from the lua stack.
////////////////////////////////////////////////////////////////////////////////
/// \{

/// \brief The default implementation.
/// \tparam T  The type.
template < typename T, typename Enable = void>
struct lua_value {};

/// \brief The implementation for integral values.
template <typename T>
struct lua_value< T, std::enable_if_t< std::is_integral<T>::value > >
{
  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a long long.
  static T get(lua_State * s, int index = -1)
  {
    if ( !lua_isnumber(s,index) )
     raise_runtime_error( std::string("Invalid conversion of type \"") +
      lua_typestring(s, index) + "\" to int."
    );
    auto i = lua_tointeger(s, index);
    lua_remove(s,index);
    return i;
  }
}; // lua_value<T> for integral


/// \brief The implementation for double.
template <typename T>
struct lua_value<T, std::enable_if_t< std::is_floating_point<T>::value > >
{
  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a double.
  static T get(lua_State * s, int index = -1)
  {
    if ( !lua_isnumber(s,index) )
     raise_runtime_error( "Invalid conversion of type \"" +
      lua_typestring(s, index) + "\" to double."
    );
    auto x = lua_tonumber(s, index);
    lua_remove(s,index);
    return x;
  }
}; // lua_value<T s.t. T is floating point>

/// \brief The implementation for bool.
template <>
struct lua_value<bool>
{
  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a boolean.
  static bool get(lua_State * s, int index = -1)
  {
    if ( !lua_isboolean(s,index) )
     raise_runtime_error( "Invalid conversion of type \"" +
      lua_typestring(s, index) + "\" to bool."
    );
    auto b = lua_toboolean(s, index);
    lua_remove(s, index);
    return b;
  }
}; // lua_value<bool>

/// \brief The implementation for std::string.
template <>
struct lua_value<std::string>
{
  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a string.
  static std::string get(lua_State * s, int index = -1)
  {
    if ( !lua_isstring(s, index) )
     raise_runtime_error( "Invalid conversion of type \"" +
      lua_typestring(s, index) + "\" to string."
    );
    auto str = lua_tostring(s, index);
    lua_remove(s, index);
    return str;
  }
}; // lua_value<string>

/// \brief The implementation for vectors.
template<
  typename T,
  typename Allocator,
  template<typename,typename> class Vector
>
struct lua_value< Vector<T,Allocator> >
{

  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a vector.
  static Vector<T,Allocator> get(lua_State * s, int index = -1)
  {
    // make sure we are accessing a table
    if ( !lua_istable(s, index) )
     raise_runtime_error( "Invalid conversion of type \"" +
      lua_typestring(s, index) + "\" to vector."
    );
    // get the size of the table
    auto n = lua_rawlen(s, -1);
    // extract the results
    Vector<T,Allocator> res;
    res.reserve(n);
    for ( int i=1; i<=n; ++i ) {
      lua_rawgeti(s, -1, i);  // push t[i]
      res.emplace_back( lua_value<T>::get(s) );
    }
    // remove it from the stack
    lua_remove(s, index);
    return res;
  }
}; // lua_value<vector>

/// \brief The implementation for vectors.
template<
  typename T,
  std::size_t N,
  template <typename,std::size_t> class Array
>
struct lua_value< Array<T,N> >
{

  /// \brief Return the value in the lua stack.
  /// \param [in] s  The lua state to query.
  /// \param [in] index  The row to access.  Defaults to the value at the top
  ///                    of the stack.
  /// \return The requested value as a vector.
  static Array<T,N> get(lua_State * s, int index = -1)
  {
    // make sure we are accessing a table
    if ( !lua_istable(s, index) )
     raise_runtime_error( "Invalid conversion of type \"" +
      lua_typestring(s, index) + "\" to vector."
    );
    // get the size of the table
    auto n = lua_rawlen(s, -1);
    if ( n != N )
      raise_runtime_error(
        "Expecting array of size" + std::to_string(N) +
        ", stack array is size " + std::to_string(n)
      );
    // extract the results
    Array<T,N> res;
    for ( int i=1; i<=std::min(n,N); ++i ) {
      lua_rawgeti(s, -1, i);  // push t[i]
      res[i-1] = lua_value<T>::get(s);
    }
    // remove it from the stack
    lua_remove(s, index);
    return res;
  }
}; // lua_value<array>

/// \}

} // ristra::

#endif // HAVE_LUA

