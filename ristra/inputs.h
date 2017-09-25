// inputs.h
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

/**\file inputs.h: main entry point for input_engine. */

#include "input_engine.h"
#include "detail/default_input_traits.h"
#include "init_value.h"

// Configure input_engine macros from build system here:
#ifdef RISTRA_DIMENSION
constexpr uint8_t default_dim = RISTRA_DIMENSION;
#else
constexpr uint8_t default_dim = 2;
#endif

namespace ristra{

using input_traits = detail::default_input_traits<default_dim>;
using default_input_engine = input_engine_t<input_traits>;

} // ristra::

// End of file
