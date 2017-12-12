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

#include<ristra-config.h>

#ifdef RISTRA_ENABLE_LUA

// user includes
#include "detail/lua_base.h"
#include "detail/lua_ref.h"
#include "detail/lua_result.h"
#include "detail/lua_utils.h"
#include "detail/lua_value.h"
#include "ristra/utils/errors.h"

// use lua
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}

#include <string>
#include <type_traits>

namespace ristra {
namespace embedded {

using lua_result_t = detail::lua_result_t;
using lua_result_uptr_t = detail::lua_result_uptr_t;
using lua_result_sptr_t = std::shared_ptr<lua_result_t>;

/**\brief Maintain a dynamically allocated Lua function with an interface that
 * is compatible with std::function.
 *
 * Note that the generic form cannot be instantiated.
 */
template <typename... T>
struct Lua_Func_Wrapper {
  Lua_Func_Wrapper()
  {
    static_assert(!std::is_same<T..., T...>::value,
      "Generic Lua_Func_Wrapper not implemented, use std::function "
      "specialization");
  }
};

/**\brief Maintain a dynamically allocated Lua function with an interface that
 * is compatible with std::function.
 *
 * Instantiate via std::function<Ret(Args...)>
 *
 * Note the lua_result_t represents the Lua function via overloaded
 * operator() that takes variable args. The returned lua_result_t is converted
 * to Ret via the as() function.
 *
 * It is the user's responsibility to make sure that Args... is consistent with
 * the Lua functions arity and type needs.
 */
template <typename Ret, typename... Args>
struct Lua_Func_Wrapper<std::function<Ret(Args...)>> {
  Ret operator()(Args... args)
  {
    auto r = lua_func_(args...).template as<Ret>();
    return r;
  }

  /**\brief Construct from unique_ptr to lua_result_t */
  explicit Lua_Func_Wrapper(lua_result_uptr_t && lf)
    : plua_func_(std::move(lf)), lua_func_(*plua_func_)
  {
  }

  /**\brief Construct from reference to lua_result_t */
  explicit Lua_Func_Wrapper(lua_result_t & lf)
    : plua_func_(std::make_shared<lua_result_t>(lf)), lua_func_(lf)
  {
  }

  // shared b/c Lua_Func_Wrapper needs to be copyable
  lua_result_sptr_t plua_func_;
  lua_result_t & lua_func_;
}; // Lua_Func_Wrapper

////////////////////////////////////////////////////////////////////////////////
/// \brief The top level object for the lua interface.
/// This is the object the user will instantiate.
////////////////////////////////////////////////////////////////////////////////
class lua_t : public detail::lua_base_t
{
 public:
  /// \brief Main constructor.
  /// \param [in] with_system  If true, load all system libraries.
  ///                          Default is true.
  lua_t(bool with_system = true) : detail::lua_base_t()
  {
    if (!state_)
      throw_runtime_error("Cannot initialize lua state.");
    // open all system libraries
    if (with_system)
      luaL_openlibs(state());
  }

  /// \brief Run a string through the lua interpreter.
  /// \param [in] script  The script to run.
  /// \return The lua error code.
  bool run_string(const std::string & script)
  {
    auto ret = luaL_dostring(state(), script.c_str());
    if (ret) {
      print_last_row();
      throw_runtime_error("Cannot load buffer.");
    }
    return ret;
  }

  /// \brief Load a file in the lua interpreter.
  /// \param [in] file  The file to load.
  void loadfile(const std::string & file)
  {
    auto ret = luaL_dofile(state(), file.c_str());
    if (ret) {
      print_last_row();
      throw_runtime_error("Cannot load file.");
    }
  }

  /// \brief Access an object in the global table.
  /// \param [in] key  The key to access.
  /// \return A lua_result_t object which points to the value of the table
  ///         lookup.
  lua_result_t operator[](const std::string & key) const &
  {
    auto s = state();
    // the function name
    lua_getglobal(s, key.c_str());
    // get the size of the object
    auto len = lua_rawlen(s, -1);
    // return the global object with a pointer to a location in the stack
    return {state_, key, detail::make_lua_ref(state_), len};
  }

  /// \brief Run a string through the lua interpreter.
  /// \param [in] script  The script to run.
  /// \return The lua error code.
  auto operator()(const std::string & script) { return run_string(script); }
}; // class lua_t

} // utils
} // ristra

#else // RISTRA_ENABLE_LUA

namespace ristra {
namespace embedded {

  struct lua_result_stub{
    template <typename T>
    bool get_value(std::string const &/**/, T &/**/) const {return false;}
  }; // lua_result_uptr_t_stub

  using lua_result_uptr_t = std::unique_ptr<lua_result_stub>;

  template <typename T>
  struct Lua_Func_Wrapper_stub{
    explicit Lua_Func_Wrapper_stub(T&& /**/){}
  }; // Lua_Func_Wrapper stub

  template <typename T> using Lua_Func_Wrapper = Lua_Func_Wrapper_stub<T>;

} // utils
} // ristra

#endif // RISTRA_ENABLE_LUA
