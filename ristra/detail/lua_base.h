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

// user includes
#include "ristra/errors.h"
#include "ristra/detail/lua_utils.h"
#include "ristra/detail/lua_value.h"

#include <iomanip>
#include <sstream>

namespace ristra {
namespace detail{

////////////////////////////////////////////////////////////////////////////////
/// \brief A base class for several of the implemented objects.
/// This class mainly contains a lua state pointer which all derived
/// classes will use.  It also has some utility member functions.
////////////////////////////////////////////////////////////////////////////////
class lua_base_t {

protected:

  /// \brief The state pointer.
  lua_state_ptr_t state_;

public:

  /// \brief Default constructor.
  lua_base_t()
    : state_( luaL_newstate(), [](lua_State * s) { lua_close(s); } )
  {}

  /// \brief Copy constructor.
  lua_base_t(const lua_state_ptr_t & state)
    : state_(state)
  {}

  /// \brief Return the raw state pointer.
  /// \remark Non-const version.
  auto state() { return state_.get(); }
  /// \brief Return the raw state pointer.
  /// \remark Const version.
  auto state() const { return state_.get(); }

  /// \brief Get the ith row of the stack.
  /// \param [in] i The row of the stack.
  /// \return A string with the type and value at the ith row.
  std::string get_row(int i) const
  {
    auto s = state();
    std::stringstream os;
    auto t = lua_type(s, i);
    switch (t) {
      case LUA_TSTRING:  // strings
        os << "string >> " << lua_tostring(s, i);
        break;
      case LUA_TBOOLEAN:  // booleans
        os << "bool   >> " << (lua_toboolean(s, i) ? "true" : "false");
        break;
      case LUA_TNUMBER:  // numbers
        os << "number >> " << lua_tonumber(s, i);
        break;
      default:  // other values
        os << "other  >> " << lua_typename(s, t);
        break;
    }
    return os.str();
  }

  /// \brief Dump the stack to an output stream/
  /// \param [in,out] os The stream to output to.
  /// \return A reference to the output stream.
  std::ostream& dump_stack(std::ostream& os) const
  {
    auto s = state();
    auto top = lua_gettop(s);
    if ( top ) {
      os << "Row : Type   >> Value" << std::endl;
      for (int i = 1; i <= top; i++) {  /* repeat for each level */
        os << std::setw(3) << i << " : ";
        os << get_row(i);
        os << std::endl;  // put a separator
      }
    }
    else {
      os << "(stack empty)" << std::endl;
    }
    return os;
  }

  /// \brief Print the last row in the stack.
  void print_last_row() const
  {
    auto s = state();
    auto top = lua_gettop(s);
    std::cerr << "Row : Type   >> Value" << std::endl;
    std::cerr << std::setw(3) << top << " : " << get_row(-1) << std::endl;
    //lua_pop(state(), 1);
  }

  /// \brief the output operator.
  /// \param [in,out] os  The output stream.
  /// \param [in] s  The object whose stack to dump.
  /// \return The output stream.
  friend std::ostream& operator<<(std::ostream& os, const lua_base_t & s)
  {
    return s.dump_stack(os);
  }
}; // class lua_base_t

} // detail::
} // ristra::

#endif // HAVE_LUA

