// init_value.cc
// T. M. Kelley
// Aug 29, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include "ristra/init_value.h"
#include "cinchtest.h"
#include "test_input_hard_coded_problems.h"
#include "test_inputs.h"

// using namespace ristra;

TEST(init_value,header_compiles){
  ASSERT_TRUE(true);
}

using real_t = test_inputs_t::real_t;
using targs_t = test_inputs_t::target_set_t;
using vector_t = test_inputs_t::vector_t;

template <typename T> using test_init_value =
  ristra::init_value_t<T,test_inputs_t>;

TEST(init_value,construct){
  /* Note this test uses test_inputs_t just so it can inspect the registries.
   * This works because the registries and target/failed sets are singletons.
   * That is, all instances of that type of the input engine have the
   * same registry instance.
   */
  test_inputs_t t;
  test_init_value<real_t> ivr("foo");
  {
    targs_t const &real_targets(t.get_target_set<real_t>());
    EXPECT_EQ(1ul,real_targets.count("foo"));
  }
  test_init_value<vector_t> ivarr_r_t("moo");
  {
    targs_t const &arr_d_targets(t.get_target_set<vector_t>());
    EXPECT_EQ(1ul,arr_d_targets.count("moo"));
  }
  t.clear_registry();
} // TEST(init_value,int)

TEST(init_value,get){
  /* This test uses the same instance provided by get_input_engine, defined
   * in inputs.h. That's because it's necessary to use that particular instance
   * as it has state variables that are not common to all instances.
   */
  test_inputs_t t;
  ristra::hard_coded_source_t *phcs =
      new ristra::hard_coded_source_t(ristra_test::make_mock_box_2d());
  t.register_hard_coded_source(phcs);
  test_init_value<real_t> ivr_final_time("final_time");

  // now resolve
  bool all_resolved = t.resolve_inputs();
  EXPECT_TRUE(all_resolved);
  // now inspect values
  real_t &final_time(ivr_final_time.get());
  EXPECT_EQ(0.21,final_time);
  t.clear_registry();
  phcs->clear_registry<test_inputs_t::traits_t::types>();
} // TEST(init_value,get)

TEST(init_value,get_with_failures){
  /* This test uses the same instance provided by get_input_engine, defined
   * in inputs.h. That's because it's necessary to use that particular instance
   * as it has state variables that are not common to all instances.
   */
  test_inputs_t t;
  ristra::hard_coded_source_t *phcs =
      new ristra::hard_coded_source_t(ristra_test::make_mock_box_2d());
  t.register_hard_coded_source(phcs);
  // some values that will resolve...
  test_init_value<real_t> ivr_final_time("final_time");
  test_init_value<vector_t> iv_xmin("xmin");
  using ics_function_t = test_inputs_t::traits_t::ics_function_t;
  test_init_value<ics_function_t> iv_ics("ics_func");
  test_init_value<ics_function_t> iv_ics_bunk("ics_bunc");
  // ...and some bogus values that will not resolve
  test_init_value<real_t> iv_foo("foo");
  test_init_value<vector_t> iv_moo("moo");

  // now resolve
  bool all_resolved = t.resolve_inputs();
  EXPECT_FALSE(all_resolved);

  // now inspect values
  real_t &final_time(ivr_final_time.get());
  EXPECT_EQ(0.21,final_time);

  EXPECT_TRUE(iv_xmin.resolved());

  ASSERT_TRUE(iv_ics.resolved());
  // ics_function_t ics(iv_ics.get());
  EXPECT_FALSE(iv_foo.resolved());
  EXPECT_FALSE(iv_moo.resolved());
  EXPECT_THROW(iv_foo.get(),std::exception);
  t.clear_registry();
  phcs->clear_registry<test_inputs_t::traits_t::types>();
} // TEST(init_value,get)

// End of file
