// default_input_traits.h
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

#include "ristra/detail/lua_result.h"
#include <functional>
#include <tuple>

namespace ristra{
namespace detail{

template <uint8_t ndim>
struct default_input_traits{
// types and constants
  static constexpr uint8_t dim = ndim;

  using real_t = double;
  using size_t = ::size_t;
  using vector_t = std::array<real_t,dim>;
  using arr_d_r_t = std::array<real_t,dim>;
  using arr_d_s_t = std::array<size_t,dim>;
  using ics_return_t   = std::tuple<real_t,arr_d_r_t,real_t>;
  using ics_function_t =
    std::function<ics_return_t(arr_d_r_t const &, real_t const & t)>;
  using types = std::tuple<real_t,
                           std::string,
                           arr_d_r_t,
                           arr_d_s_t,
                           size_t
                           ,ics_function_t
                           >;


  struct Lua_ICS_Func_Wrapper{
  // state
    lua_result_t &lua_func;
  // interface
    ics_return_t operator()(arr_d_r_t const &x, real_t const t){
      real_t d,p;
      arr_d_r_t v;
      std::tie(d, v, p) =
        lua_func(x[0], x[1], t).template as<real_t, arr_d_r_t, real_t>();
      return std::make_tuple( d, std::move(v), p);
    }

    explicit Lua_ICS_Func_Wrapper(lua_result_t &u)
        : lua_func(u) {}
  }; // struct Lua_ICS_Func_Wrapper
}; // input_traits


} // detail::
} // ristra::

// End of file
