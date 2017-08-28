// test_input_hard_coded_problems.cc
// T. M. Kelley
// May 10, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include "test_input_hard_coded_problems.h"
#include "ristra/flecsale-vector.h"

namespace ristra_test{

template <class T> using registry = spec_t::registry<T>;
using ristra::vector;

spec_t::ics_return_t<2>
ics_func_2d(vector<real_t,2> const &xs, real_t const &t){
  double const &x(xs[0]);
  double const &y(xs[1]);
  if(x < 0 && y < 0)
  {
    return {0.1,{0.0,0.0},0.125};
  }
  return {2.0,{0.0,0.0},2.0};
} // ics_func_2d

spec_t
make_mock_box_2d(){
  constexpr uint32_t dim(2u);
  using string_t = spec_t::string_t;
  using real_t = spec_t::real_t;
  using vec2r_t = std::array<real_t,dim>;
  using vec2s_t = std::array<size_t,dim>;
  using ics_f_t = spec_t::ics_function_t<dim>;
  spec_t hc;

  registry<real_t> &real_t_reg = hc.get_registry<real_t>();
  real_t_reg["final_time"] = 0.21;
  real_t_reg["CFL"] = 0.51;
  real_t_reg["gas_constant"] = 1.41;
  real_t_reg["specific_heat"] = 1.01;

  registry<size_t> &size_t_reg = hc.get_registry<size_t>();
  size_t_reg["max_steps"] = 1000001;
  size_t_reg["output_freq"] = 71;

  registry<string_t> &string_t_reg = hc.get_registry<string_t>();
  string_t_reg["prefix"] = "mock_box_2d";
  string_t_reg["suffix"] = "dat";
  string_t_reg["mesh_type"] = "box";
  string_t_reg["eos_type"] = "ideal_gas";
  string_t_reg["file"] = "shouldn't come to this";

  registry<vec2r_t> &vec2r_t_reg = hc.get_registry<vec2r_t>();
  vec2r_t_reg["xmin"] = {-0.51,-0.5};
  vec2r_t_reg["xmax"] = {0.5,0.5};

  registry<vec2s_t> &vec2s_t_reg = hc.get_registry<vec2s_t>();
  vec2s_t_reg["dimensions"] = {101,10};

  registry<ics_f_t> &ics_registry = hc.get_registry<ics_f_t>();
  ics_registry["ics_func"] = ics_func_2d;

  return hc;
} // make_mock_box_2d

} // ristra_test::


// End of file
