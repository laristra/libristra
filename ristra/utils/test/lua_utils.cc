/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to embedded lua.
////////////////////////////////////////////////////////////////////////////////

#include<cinchtest.h>
#include<ristra-config.h>

#ifdef RISTRA_ENABLE_LUA

// user includes
#include <ristra/utils/lua_utils.h>

// system includes
#include<array>
#include<iostream>


// explicitly use some stuff
using namespace ristra::utils;
using ristra::config::test_tolerance;

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the simple use of embedded lua.
///////////////////////////////////////////////////////////////////////////////
TEST(lua_utils, simple) 
{

  // setup the python interpreter
  auto state = lua_t();

  // load the test file
  state.run_string(
    "print(\"Hello World\")\n"
  );

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the simple use of embedded python.
///////////////////////////////////////////////////////////////////////////////
TEST(lua_utils, embedded) 
{

  // setup the python interpreter
  auto state = lua_t();

  // load the test file
  state.loadfile( "lua_test.lua" );

  // run a simple function and check the result
  ASSERT_EQ( 3, state["sum"]( 1, 2 ).as<int>() );
  ASSERT_NEAR( 3., state["sum"]( 1, 2 ).as<double>(), test_tolerance );

  // try with different arguments
  ASSERT_EQ( 3, state["sum"]( 1., 2. ).as<int>() );
  ASSERT_NEAR( 3., state["sum"]( 1., 2. ).as<double>(), test_tolerance );

  // try a function that returns tuples
  auto tup1 = state["split"]( 1, 2.5 ).as<int,double>();
  ASSERT_EQ( std::forward_as_tuple(1,2.5), tup1 );

  // access a global variable
  ASSERT_EQ( 4, state["foo"].as<int>() );

  // access table elements
  auto tab1 = state["mytable"];
  ASSERT_EQ( "hi", tab1[3].as<std::string>() );
  ASSERT_EQ( 4.5, tab1["there"].as<double>() );
  ASSERT_EQ( 6, tab1["func"]().as<int>() );

  // access arrays
  auto arr1 = state["bar"];  
  auto arr1_vec_ans = std::vector<int>{1,2,3};
  auto arr1_arr_ans = std::array<int,3>{1,2,3};
  arr1.as<std::array<int,3>>();
  ASSERT_EQ( arr1_vec_ans, arr1.as<std::vector<int>>() );
  //ASSERT_EQ( arr1_arr_ans, arr1.as<std::array<int,3>>() );

  // access non-existant data
  ASSERT_TRUE(state["not_there"].empty());
  ASSERT_TRUE(arr1["not_there"].empty());
  
} // TEST

#endif // HAVE_LUA
