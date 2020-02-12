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
#include <ristra/embedded/embed_lua.h>
#include <ristra/math/vector.h>

// system includes
#include<array>
#include<iostream>


// explicitly use some stuff
using namespace ristra::embedded;
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
  auto arr1_as_arr = arr1.as<std::array<int,3>>();
  ASSERT_EQ( arr1_vec_ans, arr1.as<std::vector<int>>() );
  ASSERT_EQ( arr1_arr_ans, arr1_as_arr );

  auto arr1_as_vector_t = arr1.as< ristra::math::vector<int,3> >();

  // access non-existant data
  ASSERT_TRUE(state["not_there"].empty());
  ASSERT_TRUE(arr1["not_there"].empty());

  // test more complex function
  {
    double d = -1.0, p = -1.0, t = 3.14159;
    using vector_t = std::array<double, 3>;
    vector_t v{-1.0, -1.0, -1.0};
    vector_t x{1.0, 2.0, 3.0};
    auto lua_f = state["ics"]; //
    auto lua_res = lua_f(x, t);
    std::tie(d, v, p) = lua_res.as<double, vector_t, double>();
  }
} // TEST(lua_utils, embedded)

TEST(lua_utils, funcs)
{
  using rettuple = std::tuple<double, std::array<double, 2>, double>;
  using dcr = double const &;
  using func_t = std::function<rettuple(dcr, dcr, dcr)>;

  auto state = lua_t();
  state.loadfile("mock_box_2d.lua");

  auto hydro = state["hydro"];
  lua_result_t lua_f = hydro["ics"];
  {
    rettuple tup = lua_f(1.0, 1.0, 1.0).as<rettuple>();
    double d1 = std::get<0>(tup);
    std::array<double, 2> a = std::get<1>(tup);
    double d2 = std::get<2>(tup);

    EXPECT_EQ(d1, 1.0);
    EXPECT_EQ(d2, 1.0);
    EXPECT_EQ(a[0], 0.0);
    EXPECT_EQ(a[1], 0.0);
  }
  // ok, now try to store the lua result deal as a std::function
  // Lua_Func_Wrapper<rettuple, dcr,dcr,dcr> fw(lua_f);
  Lua_Func_Wrapper<func_t> fw(lua_f);
  {
    // auto tup = fw.template <rettuple, dcr,dcr,dcr>(1.0,1.0,1.0);
    auto tup = fw(1.0, 1.0, 1.0);
    double d1 = std::get<0>(tup);
    std::array<double, 2> a = std::get<1>(tup);
    double d2 = std::get<2>(tup);

    EXPECT_EQ(d1, 1.0);
    EXPECT_EQ(d2, 1.0);
    EXPECT_EQ(a[0], 0.0);
    EXPECT_EQ(a[1], 0.0);
  }
  func_t cpp_f(fw);
  {
    auto tup = cpp_f(1.0, 1.0, 1.0);
    double d1 = std::get<0>(tup);
    std::array<double, 2> a = std::get<1>(tup);
    double d2 = std::get<2>(tup);

    EXPECT_EQ(d1, 1.0);
    EXPECT_EQ(d2, 1.0);
    EXPECT_EQ(a[0], 0.0);
    EXPECT_EQ(a[1], 0.0);
  }

} // TEST(lua_utils,funcs){

#endif // RISTRA_ENABLE_LUA
