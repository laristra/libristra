// input_engine.cc
// T. M. Kelley
// May 08, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include<ristra-config.h>

#include "ristra/initialization/input_engine.h"
#include "cinchtest.h"
// #include "ristra/flecsale-vector.h"
#include <array>
#include "test_input_hard_coded_problems.h"
#include "test_inputs.h"

using namespace ristra;

TEST(input_engine, header_compiles) { ASSERT_TRUE(true); }

using real_t = double;
using vector_t = std::array<real_t, 2>;
using string_t = std::string;

using ics_return_t = std::tuple<real_t, vector_t, real_t>;
using ics_function_t =
  std::function<ics_return_t(vector_t const &, real_t const & t)>;

TEST(input_engine, instantiate)
{
  test_inputs_t t;
  ASSERT_TRUE(true);
} // TEST(input_engine,instantiate){

ics_return_t ICS_Func(vector_t, real_t)
{
  return {real_t(), vector_t(), real_t()};
}

TEST(input_engine, register_target)
{
  using targs_t = test_inputs_t::target_set_t;
  using ics_f_t = ics_function_t;
  test_inputs_t t;
  t.clear_registry();
  t.register_target<double>("foo");
  {
    targs_t const & real_targets(t.get_target_set<double>());
    EXPECT_EQ(1ul, real_targets.count("foo"));
  }
  t.register_target<string_t>("gnu");
  {
    targs_t const & string_targets(t.get_target_set<string_t>());
    EXPECT_EQ(1ul, string_targets.count("gnu"));
    targs_t exp_targs = {"gnu"};
    EXPECT_EQ(exp_targs, string_targets);
  }
  t.register_target<string_t>("flu");
  t.register_target<string_t>("zoo");
  {
    targs_t const & string_targets(t.get_target_set<string_t>());
    targs_t exp_targs = {"gnu", "flu", "zoo"};
    EXPECT_EQ(exp_targs, string_targets);
  }
  t.register_target<ics_f_t>("ics");
  {
    targs_t const & ics_targets(t.get_target_set<ics_f_t>());
    targs_t exp_targs = {"ics"};
    EXPECT_EQ(exp_targs, ics_targets);
  }
  t.register_target<ics_f_t>("jcs");
  {
    targs_t const & ics_targets(t.get_target_set<ics_f_t>());
    targs_t exp_targs = {"jcs", "ics"};
    EXPECT_EQ(exp_targs, ics_targets);
  }
  t.register_target<string_t>("moo");
  {
    targs_t const & string_targets(t.get_target_set<string_t>());
    targs_t exp_targs = {"gnu", "flu", "moo", "zoo"};
    EXPECT_EQ(exp_targs, string_targets);
  }
  t.register_target<size_t>("n_ns");
  {
    targs_t const & size_targets(t.get_target_set<size_t>());
    targs_t exp_targs = {"n_ns"};
    EXPECT_EQ(exp_targs, size_targets);
  }
  t.register_target<input_traits::arr_d_r_t>("xmin");
  {
    targs_t const & array_2_targets(
      t.get_target_set<input_traits::arr_d_r_t>());
    targs_t exp_targs = {"xmin"};
    EXPECT_EQ(exp_targs, array_2_targets);
  }
  t.clear_registry();
} // TEST(input_engine,instantiate){

TEST(input_engine, resolve_inputs_from_hc)
{
  using targs_t = test_inputs_t::target_set_t;
  using ics_f_t = ics_function_t;
  using targets_t = test_inputs_t::target_set_t;
  using vec2r_t = input_traits::arr_d_r_t;
  using vec2s_t = input_traits::arr_d_s_t;

  test_inputs_t t;
  targets_t real_t_targets = {
    "CFL", "final_time", "gas_constant", "specific_heat"};

  targets_t size_t_targets = {"output_freq", "max_steps"};
  targets_t string_t_targets = {
    "prefix", "suffix", "mesh_type", "eos_type", "file"};

  targets_t vec2r_targets = {"xmin", "xmax"};
  targets_t vec2s_targets = {"dimensions"};
  targets_t ics_targets = {"ics_func"};

  t.register_targets<real_t>(real_t_targets);
  t.register_targets<size_t>(size_t_targets);
  t.register_targets<string_t>(string_t_targets);
  t.register_targets<vec2r_t>(vec2r_targets);
  t.register_targets<vec2s_t>(vec2s_targets);
  t.register_targets<ics_function_t>(ics_targets);
  // no lua function to be got
  // t.register_targets<lua_result_uptr_t>(ics_targets);

  // string_t fname("mock_box_2d.lua");
  // lua_source_t * pls = new lua_source_t(fname);
  // t.register_lua_source(pls);

  hard_coded_source_t * phcs =
    new hard_coded_source_t(ristra_test::make_mock_box_2d());
  void *hcs_address_0(&(*phcs));
  EXPECT_FALSE(t.has_hard_coded_source());
  t.register_hard_coded_source(phcs);
  EXPECT_TRUE(t.has_hard_coded_source());
  EXPECT_FALSE(t.has_lua_source());

  hard_coded_source_t &hcs_ref(t.get_hard_coded_source());
  void *hcs_address_1(&hcs_ref);
  EXPECT_EQ(hcs_address_0,hcs_address_1);

  bool all_resolved = t.resolve_inputs();
  EXPECT_TRUE(all_resolved);
  EXPECT_EQ(0.51, t.get_value<real_t>("CFL"));
  EXPECT_EQ(1.41, t.get_value<real_t>("gas_constant"));
  EXPECT_EQ(1.01, t.get_value<real_t>("specific_heat"));
  EXPECT_EQ(0.21, t.get_value<real_t>("final_time"));
  EXPECT_EQ(71, t.get_value<size_t>("output_freq"));
  EXPECT_EQ(1000001, t.get_value<size_t>("max_steps"));
  EXPECT_EQ("mock_box_2d", t.get_value<string_t>("prefix"));
  EXPECT_EQ("dat", t.get_value<string_t>("suffix"));
  EXPECT_EQ("box", t.get_value<string_t>("mesh_type"));
  EXPECT_EQ("ideal_gas", t.get_value<string_t>("eos_type"));
  EXPECT_EQ("shouldn't come to this", t.get_value<string_t>("file"));

  vec2r_t exp_xmins = {-0.51, -0.5};
  vec2r_t exp_xmaxs = {0.5, 0.5};
  EXPECT_EQ(exp_xmins, t.get_value<vec2r_t>("xmin"));
  EXPECT_EQ(exp_xmaxs, t.get_value<vec2r_t>("xmax"));

  vec2s_t exp_dims = {101, 10};
  EXPECT_EQ(exp_dims, t.get_value<vec2s_t>("dimensions"));

  {
    ics_function_t f(t.get_value<ics_function_t>("ics_func"));
    {
      auto result = f({-1, -2}, 23);
      ics_return_t exp_result = {0.1, {0.0, 0.0}, 0.125};
      EXPECT_EQ(exp_result, result);
    }
    {
      auto result = f({1, 2}, 123000000);
      ics_return_t exp_result = {2.0, {0.0, 0.0}, 2.0};
      EXPECT_EQ(exp_result, result);
    }
  }
  t.clear_registry();
  phcs->clear_registry<input_traits::types>();
} // TEST(input_engine,resolve_inputs_from_hc){

TEST(input_engine, resolve_inputs_from_hc_with_failures)
{
  using targs_t = test_inputs_t::target_set_t;
  using ics_f_t = ics_function_t;
  using targets_t = test_inputs_t::target_set_t;
  using vec2r_t = input_traits::arr_d_r_t;
  using vec2s_t = input_traits::arr_d_s_t;

  test_inputs_t t;
  targets_t real_t_targets = {
    "CFL", "final_time", "gas_constant", "specific_heat"};
  targets_t size_t_targets = {"output_freq", "max_steps"};
  targets_t string_t_targets = {
    "prefix", "suffix", "mesh_type", "eos_type", "file"};
  targets_t vec2r_targets = {"xmin", "xmax"};
  targets_t vec2s_targets = {"dimensions"};
  targets_t ics_targets = {"ics_BUNK", "ics_func"};

  t.register_targets<real_t>(real_t_targets);
  t.register_targets<size_t>(size_t_targets);
  t.register_targets<string_t>(string_t_targets);
  t.register_targets<vec2r_t>(vec2r_targets);
  t.register_targets<vec2s_t>(vec2s_targets);
  t.register_targets<ics_function_t>(ics_targets);

  hard_coded_source_t * phcs =
    new hard_coded_source_t(ristra_test::make_mock_box_2d());
  t.register_hard_coded_source(phcs);

  bool all_resolved = t.resolve_inputs();
  EXPECT_FALSE(all_resolved);

  EXPECT_EQ(0.51, t.get_value<real_t>("CFL"));
  EXPECT_EQ(1.41, t.get_value<real_t>("gas_constant"));
  EXPECT_EQ(1.01, t.get_value<real_t>("specific_heat"));
  EXPECT_EQ(0.21, t.get_value<real_t>("final_time"));

  EXPECT_EQ(71, t.get_value<size_t>("output_freq"));
  EXPECT_EQ(1000001, t.get_value<size_t>("max_steps"));

  EXPECT_EQ("mock_box_2d", t.get_value<string_t>("prefix"));
  EXPECT_EQ("dat", t.get_value<string_t>("suffix"));
  EXPECT_EQ("box", t.get_value<string_t>("mesh_type"));
  EXPECT_EQ("ideal_gas", t.get_value<string_t>("eos_type"));
  EXPECT_EQ("shouldn't come to this", t.get_value<string_t>("file"));

  vec2r_t exp_xmins = {-0.51, -0.5};
  vec2r_t exp_xmaxs = {0.5, 0.5};
  EXPECT_EQ(exp_xmins, t.get_value<vec2r_t>("xmin"));
  EXPECT_EQ(exp_xmaxs, t.get_value<vec2r_t>("xmax"));

  vec2s_t exp_dims = {101, 10};
  EXPECT_EQ(exp_dims, t.get_value<vec2s_t>("dimensions"));

  targets_t const & failures_lua_r_t =
    t.get_failed_target_set<ics_function_t>();
  targets_t const exp_fails = {"ics_BUNK"};
  size_t const n_unresolved(failures_lua_r_t.size());
  size_t const exp_n_unresolved(1lu);
  EXPECT_EQ(n_unresolved, exp_n_unresolved);
  EXPECT_EQ(failures_lua_r_t, exp_fails);
  t.clear_registry();
  phcs->clear_registry<input_traits::types>();
} // TEST(input_engine,resolve_inputs_from_hc_with_failures){

#ifdef RISTRA_ENABLE_LUA

TEST(input_engine, resolve_inputs_from_lua)
{
  using targs_t = test_inputs_t::target_set_t;
  using ics_f_t = ics_function_t;
  using targets_t = test_inputs_t::target_set_t;
  using vec2r_t = input_traits::arr_d_r_t;
  using vec2s_t = input_traits::arr_d_s_t;

  test_inputs_t t;
  targets_t real_t_targets = {
    "CFL", "final_time", "gas_constant", "specific_heat"};
  targets_t size_t_targets = {"output_freq", "max_steps"};
  targets_t string_t_targets = {
    "prefix", "suffix", "mesh_type", "eos_type", "file"};
  targets_t vec2r_targets = {"xmin", "xmax"};
  targets_t vec2s_targets = {"dimensions"};
  targets_t ics_targets = {"ics_func"};

  t.register_targets<real_t>(real_t_targets);
  t.register_targets<size_t>(size_t_targets);
  t.register_targets<string_t>(string_t_targets);
  t.register_targets<vec2r_t>(vec2r_targets);
  t.register_targets<vec2s_t>(vec2s_targets);
  t.register_targets<utils::lua_result_uptr_t>(ics_targets);

  t.register_targets<ics_function_t>(ics_targets);

  string_t fname("mock_box_2d.lua");
  // lua_source_t * pls = new lua_source_t(fname);
  lua_source_ptr_t pls(mk_lua(fname));
  pls -> register_table("eos","hydro");
  pls -> register_value("eos_type","eos","type");
  pls -> register_value("gas_constant","eos");
  pls -> register_value("specific_heat","eos");

  t.register_lua_source(pls.release());

  hard_coded_source_t * phcs =
    new hard_coded_source_t(ristra_test::make_mock_box_2d());
  t.register_hard_coded_source(phcs);

  bool all_resolved = t.resolve_inputs();
  EXPECT_TRUE(all_resolved);

  EXPECT_EQ(0.5, t.get_value<real_t>("CFL"));
  EXPECT_EQ(1.4, t.get_value<real_t>("gas_constant"));
  EXPECT_EQ(1.0, t.get_value<real_t>("specific_heat"));
  EXPECT_EQ(0.2, t.get_value<real_t>("final_time"));
  EXPECT_EQ(7, t.get_value<size_t>("output_freq"));
  EXPECT_EQ(1000000, t.get_value<size_t>("max_steps"));

  EXPECT_EQ("mock_box_2d", t.get_value<string_t>("prefix"));
  EXPECT_EQ("dat", t.get_value<string_t>("suffix"));
  EXPECT_EQ("box", t.get_value<string_t>("mesh_type"));
  EXPECT_EQ("ideal_gas", t.get_value<string_t>("eos_type"));
  EXPECT_EQ("shouldn't come to this", t.get_value<string_t>("file"));

  vec2r_t exp_xmins = {-0.5, -0.5};
  vec2r_t exp_xmaxs = {0.5, 0.5};
  EXPECT_EQ(exp_xmins, t.get_value<vec2r_t>("xmin"));
  EXPECT_EQ(exp_xmaxs, t.get_value<vec2r_t>("xmax"));

  vec2s_t exp_dims = {10, 10};
  EXPECT_EQ(exp_dims, t.get_value<vec2s_t>("dimensions"));

  // original get_ics_function path
  // {
  //   ics_function_t f(t.get_ics_function("ics_func"));
  //   {
  //     auto result = f({-1,-2},23);
  //     ics_return_t exp_result = {0.125,{0.0,0.0},0.1};
  //     EXPECT_EQ(exp_result,result);
  //   }
  //   {
  //     auto result = f({1,2},123000000);
  //     ics_return_t exp_result = {1.0,{0.0,0.0},1.0};
  //     EXPECT_EQ(exp_result,result);
  //   }
  // }
  // new get_value<Callable_T> path
  {
    ics_function_t f(t.get_value<ics_function_t>("ics_func"));
    {
      auto result = f({-1, -2}, 23);
      ics_return_t exp_result = {0.125, {0.0, 0.0}, 0.1};
      EXPECT_EQ(exp_result, result);
    }
    {
      auto result = f({1, 2}, 123000000);
      ics_return_t exp_result = {1.0, {0.0, 0.0}, 1.0};
      EXPECT_EQ(exp_result, result);
    }
  }
  t.clear_registry();
  phcs->clear_registry<input_traits::types>();
  // delete pls;
} // TEST(input_engine,resolve_inputs_from_lua){

#endif // RISTRA_ENABLE_LUA

// End of file
