// inputs.h
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

/**\file inputs.h: main entry point for input_engine. */

#include "input_engine.h"
#include "detail/default_input_traits.h"

// Configure input_engine macros from build system here:
constexpr uint8_t default_dim = 2;

namespace ristra{

using input_traits = detail::default_input_traits<default_dim>;
using input_engine = input_engine_t<input_traits>;

input_engine &get_input_engine(){
  static input_engine the_engine;
  return the_engine;
}

/**\brief trigger the input engine to resolve its inputs from
 * the sources registered to it.
 *
 * \return whether all inputs were successfully resolved.
 */
bool resolve_inputs(){ return get_input_engine().resolve_inputs(); }

} // ristra::

// End of file
