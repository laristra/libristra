// input_source.cc
// T. M. Kelley
// May 08, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include<ristra-config.h>

#include "ristra/initialization/input_source.h"
#include <array>
#include "cinchtest.h"

TEST(input_source, compiles) { EXPECT_TRUE(true); } // smoke

TEST(hard_coded_source_t, instantiate)
{
  using namespace ristra;
  hard_coded_source_t ps;
  EXPECT_TRUE(true);
}

template <class T>
using reg = ristra::hard_coded_source_t::registry<T>;

TEST(input_source, hard_coded_source_t_set_registry)
{
  using namespace ristra;
  using real_t = hard_coded_source_t::real_t;
  using string_t = hard_coded_source_t::string_t;
  hard_coded_source_t ps;
  reg<real_t> exp_reg = {{"CFL", 257.4}, {"dtmax", 2.3e6}};
  ps.set_registry<real_t>(exp_reg);
  EXPECT_EQ(exp_reg, ps.get_registry<real_t>());

  reg<size_t> sz_reg = {{"n_steps", 1000000000UL}, {"n_zones_x", 30000},
    {"n_zones_y", 30000}, {"n_zones_z", 30000}, {"CFL", 12}};
  ps.set_registry<size_t>(sz_reg);
  EXPECT_EQ(sz_reg, ps.get_registry<size_t>());
  EXPECT_EQ(exp_reg, ps.get_registry<real_t>());

  reg<string_t> st_reg = {
    {"mesh_type", "useful"}, {"eos_type", "fictional"}, {"CFL", "indubitable"}};
  ps.set_registry<string_t>(st_reg);
  EXPECT_EQ(st_reg, ps.get_registry<string_t>());
  EXPECT_EQ(sz_reg, ps.get_registry<size_t>());
  EXPECT_EQ(exp_reg, ps.get_registry<real_t>());
}

TEST(input_source, hard_coded_source_t_get_value)
{
  using namespace ristra;
  using real_t = hard_coded_source_t::real_t;
  using string_t = hard_coded_source_t::string_t;
  hard_coded_source_t ps;

  reg<real_t> exp_reg = {{"CFL", 257.4}, {"dtmax", 2.3e6}};
  ps.set_registry<real_t>(exp_reg);
  reg<size_t> sz_reg = {{"n_steps", 1000000000UL}, {"n_zones_x", 30000},
    {"n_zones_y", 30000}, {"n_zones_z", 30000}, {"CFL", 12}};
  ps.set_registry<size_t>(sz_reg);
  reg<string_t> st_reg = {
    {"mesh_type", "useful"}, {"eos_type", "fictional"}, {"CFL", "indubitable"}};
  ps.set_registry<string_t>(st_reg);

  {
    double d_cfl(-42.0);
    bool ok = ps.get_value("CFL", d_cfl);
    EXPECT_TRUE(ok);
    EXPECT_EQ(d_cfl, 257.4);
    d_cfl = -42.0;
    ok = ps.get_value("CFM", d_cfl);
    EXPECT_FALSE(ok);
    EXPECT_EQ(d_cfl, -42.0);
  }
  {
    size_t n_steps(2);
    bool ok = ps.get_value("n_steps", n_steps);
    EXPECT_TRUE(ok);
    EXPECT_EQ(n_steps, 1000000000UL);
    n_steps = 2;
    ok = ps.get_value("m_steps", n_steps);
    EXPECT_FALSE(ok);
    EXPECT_EQ(n_steps, 2);
  }
} // TEST(hard_coded_source_t,get_value){

#ifdef RISTRA_ENABLE_LUA

TEST(input_source, lua_source_t_instantiate)
{
  using namespace ristra;
  using string_t = lua_source_t::string_t;
  string_t fname("mock_box_2d.lua");
  lua_source_t ls(fname);
  EXPECT_TRUE(true);
}

template <class T>
using array_t = std::array<T, 2>;

TEST(input_source, lua_source_t_get_value)
{
  using namespace ristra;
  using string_t = lua_source_t::string_t;
  using real_t = lua_source_t::real_t;
  string_t fname("mock_box_2d.lua");
  lua_source_t ls(fname);
  {
    string_t prefix;
    bool ok = ls.get_value<string_t>("prefix", prefix);
    EXPECT_EQ("mock_box_2d", prefix);
    EXPECT_TRUE(ok);
  }
  {
    string_t suffix;
    bool ok = ls.get_value<string_t>("suffix", suffix);
    EXPECT_EQ("dat", suffix);
    EXPECT_TRUE(ok);
  }
  {
    string_t output_freq;
    bool ok = ls.get_value<string_t>("output_freq", output_freq);
    EXPECT_EQ("7", output_freq);
    EXPECT_TRUE(ok);
  }
  {
    string_t mesh_type;
    bool ok = ls.get_value<string_t>("mesh_type", mesh_type);
    EXPECT_EQ("box", mesh_type);
    EXPECT_TRUE(ok);
  }
  {
    ls.register_table("eos","hydro");
    ls.register_value("eos_type","eos","type");
    ls.register_value("gas_constant","eos");
    ls.register_value("specific_heat","eos");

    string_t eos_type;
    bool ok = ls.get_value<string_t>("eos_type", eos_type);
    EXPECT_EQ("ideal_gas", eos_type);
    EXPECT_TRUE(ok);

    real_t gas_constant;
    ok = ls.get_value<real_t>("gas_constant", gas_constant);
    EXPECT_EQ(1.4, gas_constant);
    EXPECT_TRUE(ok);

    real_t specific_heat;
    ok = ls.get_value<real_t>("specific_heat", specific_heat);
    EXPECT_EQ(1.0, specific_heat);
    EXPECT_TRUE(ok);
  }
  {
    real_t final_time;
    bool ok = ls.get_value<real_t>("final_time", final_time);
    EXPECT_EQ(0.2, final_time);
    EXPECT_TRUE(ok);
  }
  {
    real_t CFL;
    bool ok = ls.get_value<real_t>("CFL", CFL);
    EXPECT_EQ(0.5, CFL);
    EXPECT_TRUE(ok);
  }
  {
    array_t<int> dimensions;
    bool ok = ls.get_value<array_t<int>>("dimensions", dimensions);
    array_t<int> exp_dims = {10, 10};
    EXPECT_EQ(exp_dims, dimensions);
    EXPECT_TRUE(ok);
  }
  {
    array_t<real_t> xmin;
    bool ok = ls.get_value<array_t<real_t>>("xmin", xmin);
    array_t<real_t> exp_dims = {-0.5, -0.5};
    EXPECT_EQ(exp_dims, xmin);
    EXPECT_TRUE(ok);
  }
  {
    array_t<real_t> xmax;
    bool ok = ls.get_value<array_t<real_t>>("xmax", xmax);
    array_t<real_t> exp_dims = {0.5, 0.5};
    EXPECT_EQ(exp_dims, xmax);
    EXPECT_TRUE(ok);
  }
  // test adding a table later on
  ls.register_table("fooble", "hydro");
  ls.register_value("acoustich", "fooble", "acoustik");
  ls.register_value("volyme", "fooble");
  ls.register_value("grouth", "fooble");
  {
    real_t acoustik = 0.0;
    bool ok = ls.get_value<real_t>("acoustich", acoustik);
    EXPECT_TRUE(ok);
    EXPECT_EQ(1.01, acoustik);
  }
  {
    real_t volyme = 0.0;
    bool ok = ls.get_value<real_t>("volyme", volyme);
    EXPECT_TRUE(ok);
    EXPECT_EQ(9.8, volyme);
  }
  {
    real_t grouth = 0.0;
    bool ok = ls.get_value<real_t>("grouth", grouth);
    EXPECT_TRUE(ok);
    EXPECT_EQ(0.25, grouth);
  }
  // now test get_size
  {
    ls.register_value("materials","hydro");
    size_t sz = ls.get_size("materials");
    EXPECT_EQ(3u,sz);
    size_t sz_fooble = ls.get_size("fooble");
    EXPECT_EQ(0u,sz_fooble);
  }
} // TEST(input_source, lua_source_t_get_value)

TEST(input_source, lua_source_t_get_table)
{
  using namespace ristra;
  using string_t = lua_source_t::string_t;
  using real_t = lua_source_t::real_t;
  string_t fname("mock_box_2d.lua");
  lua_source_t ls(fname);
  embedded::lua_result_t &hydro_input(ls.get_table("hydro"));
  embedded::lua_result_t eos(hydro_input["eos"]);
  std::string eos_type(lua_try_access_as(eos,"type",std::string));
  std::string exp_eos_type("ideal_gas");
  EXPECT_TRUE(exp_eos_type == eos_type);
}

#endif // RISTRA_ENABLE_LUA

// End of file
