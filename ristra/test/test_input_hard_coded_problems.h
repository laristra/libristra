// test_input_hard_coded_problems.h
// T. M. Kelley
// May 10, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved


#pragma once

#include "input_source.h"

namespace ristra_test{

using real_t = double;

/* To create a hard-coded test problem, simply take a hard_coded_source
 * and register data with it. */
using spec_t = ristra::hard_coded_source_t;

spec_t make_mock_box_2d();

} // ristra_test::

// End of file
