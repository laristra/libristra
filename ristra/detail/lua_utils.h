/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016-7 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Utility types and functions for all ristra Lua files
////////////////////////////////////////////////////////////////////////////////
#pragma once

#ifdef HAVE_LUA

#ifndef LUA_ACCESS_H_INCLUDED
#error "Use top-level entry point, lua_access.h!!"
#endif

// user includes
#include "ristra/errors.h"

// use lua
extern "C" {
  #include <lua.h>
}

#include <memory>
#include <string>

namespace ristra {
namespace detail{

#define lua_try_access_as(state, key, ...)                                     \
  (!state[key].empty()) ?                                                      \
    state[key].template as<__VA_ARGS__>() :                                    \
    throw std::runtime_error(                                                  \
      "\'" + state[key].name() +                                               \
      "\' does not exist in the lua state you are accessing."                  \
    )

#define lua_try_access(state, key)                                             \
  (!state[key].empty()) ?                                                      \
    state[key] :                                                               \
    throw std::runtime_error(                                                  \
      "\'" + state[key].name() +                                               \
      "\' does not exist in the lua state you are accessing."                  \
    )

///!\brief Get lua type as std::string
inline std::string lua_typestring(lua_State * s, int index)
{
  return lua_typename(s, lua_type(s, index));
}

//! \brief Use a shared pointer to the lua state.
//! Multiple objects may use the same lua state, so we don't want to
//! destroy it unless all objects are destroyed.
using lua_state_ptr_t = std::shared_ptr<lua_State>;

} // detail::
} // ristra::

#endif // HAVE_LUA

