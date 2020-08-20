/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/tasks.h"

// system includes
#include<gtest/gtest.h>
#include<iostream>
#include<vector>

// explicitly use some stuff
using std::cout;
using std::endl;
using std::vector;

using real_t   = double;
using vector_t = vector<real_t>;

using namespace ristra::utils;

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the automatic task generator.
///////////////////////////////////////////////////////////////////////////////
TEST(tasks, simple) {

  // create the task
  auto simple_function = [](auto && a, auto && b, auto && c) 
    { c = a + b; };

  vector_t a = { 1.0 }, b = { 2.0 };
  vector_t c = { 0.0 };
  simple_task( simple_function, a, b, c );
  ASSERT_EQ( c[0], 3.0 );
  

} // TEST
