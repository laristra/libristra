// default_input_traits.h
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

#include "ristra/detail/lua_result.h"
#include <functional>
#include <string>
#include <tuple>

namespace ristra{
namespace detail{

template <size_t ndim>
struct default_input_traits{
// types and constants
  static constexpr size_t dim = ndim;

  using real_t = double;
  using string_t = std::string;
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

}; // input_traits


} // detail::
} // ristra::

// End of file
