/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016-7 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Ristra entry point for access to Lua interpreter.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#define LUA_ACCESS_H_INCLUDED

#ifdef HAVE_LUA

// user includes
#include "ristra/errors.h"
#include "ristra/detail/lua_base.h"
#include "ristra/detail/lua_ref.h"
#include "ristra/detail/lua_result.h"
#include "ristra/detail/lua_utils.h"
#include "ristra/detail/lua_value.h"

// use lua
extern "C" {
  #include <lua.h>
  #include <lualib.h>
  #include <lauxlib.h>
}

#include <string>

namespace ristra {

////////////////////////////////////////////////////////////////////////////////
/// \brief The top level object for the lua interface.
/// This is the object the user will instantiate.
////////////////////////////////////////////////////////////////////////////////
class lua_t : public lua_base_t {

public:

  /// \brief Main constructor.
  /// \param [in] with_system  If true, load all system libraries.
  ///                          Default is true.
  lua_t(bool with_system = true) : lua_base_t()
  {
    if ( !state_ )
      raise_runtime_error("Cannot initialize lua state.");
    // open all system libraries
    if ( with_system )
      luaL_openlibs(state());
  }

  /// \brief Run a string through the lua interpreter.
  /// \param [in] script  The script to run.
  /// \return The lua error code.
  bool run_string( const std::string & script )
  {
    auto ret = luaL_dostring(state(),script.c_str());
    if ( ret ) {
      print_last_row();
      raise_runtime_error("Cannot load buffer.");
    }
    return ret;
  }

  /// \brief Load a file in the lua interpreter.
  /// \param [in] file  The file to load.
  void loadfile( const std::string & file )
  {
    auto ret = luaL_dofile(state(),file.c_str());
    if ( ret ) {
      print_last_row();
      raise_runtime_error("Cannot load file.");
    }
  }

  /// \brief Access an object in the global table.
  /// \param [in] key  The key to access.
  /// \return A lua_result_t object which points to the value of the table
  ///         lookup.
  lua_result_t operator[]( const std::string & key ) const &
  {
    auto s = state();
    // the function name
    lua_getglobal(s, key.c_str());
    // get the size of the object
    auto len = lua_rawlen(s, -1);
    // return the global object with a pointer to a location in the stack
    return { state_, key, make_lua_ref(state_), len };
  }

  /// \brief Run a string through the lua interpreter.
  /// \param [in] script  The script to run.
  /// \return The lua error code.
  auto operator()( const std::string & script )
  {
    return run_string( script );
  }
}; // class lua_t

} // ristra::

#endif // HAVE_LUA

