// test_inputs.h
// T. M. Kelley
// Sep 25, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#pragma once

#include "ristra/initialization/detail/default_input_traits.h"
#include "ristra/initialization/init_value.h"
#include "ristra/initialization/input_engine.h"

namespace ristra
{
// Configure input_engine macros from build system here:
#ifdef RISTRA_DIMENSION
constexpr uint8_t default_dim = RISTRA_DIMENSION;
#else
constexpr uint8_t default_dim = 2;
#endif

using input_traits = detail::default_input_traits<default_dim>;
using default_input_engine = input_engine_t<input_traits>;

} // ristra::

struct test_inputs_t : public ristra::default_input_engine {
 public:
  using base_t = ristra::default_input_engine;
  using traits_t = base_t::traits_t;

  /**\brief relay the base class's state for testing */
  template <class T>
  base_t::registry<T> & get_registry()
  {
    return base_t::get_registry<T>();
  } // get_registry

  /**\brief relay the base class's state for testing */
  template <class T>
  base_t::target_set_t & get_target_set()
  {
    return base_t::get_target_set<T>();
  } // get_registry

  /**\brief relay the base class's state for testing */
  template <class T>
  base_t::target_set_t & get_failed_target_set()
  {
    return base_t::get_failed_target_set<T>();
  } // get_registry

}; // struct test_inputs_t

// End of file
