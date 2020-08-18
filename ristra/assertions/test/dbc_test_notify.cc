// dbc_test_no_assert.cc
// T. M. Kelley
// May 02, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

/* Test will take control of the test environment */
#include<gtest/gtest.h>
#include<ristra/ristra-config.h>

// #if defined RISTRA_REQUIRE_ON && defined RISTRA_DBC_NOTIFY

#ifdef RISTRA_DBC_THROW
#undef RISTRA_DBC_THROW
#endif

#ifndef RISTRA_DBC_NOTIFY
#define RISTRA_DBC_NOTIFY
#endif

#ifndef RISTRA_REQUIRE_ON
#define RISTRA_REQUIRE_ON
#endif

#include "ristra/assertions/dbc.h"

using namespace ristra::assertions::dbc;

TEST(dbc_notify, compiles) { ASSERT_TRUE(true); }

/**\brief Is s1 a substring of s2? */
inline bool is_substring_of(std::string const & s1, std::string const & s2)
{
  return s2.find(s1) != std::string::npos;
}

std::ostream * p_temp = nullptr;

namespace
{
// switch DBC output stream to p_o
void divert_stream(std::ostream * p_o)
{
  p_temp = p_str;
  p_str = p_o;
};
// switch DBC output back to original value
std::ostream * restore_stream()
{
  std::ostream * p2 = p_str;
  p_str = p_temp;
  return p2;
}
} // anonymous::

/**\brief Check that s1 is a substring of s2, print them if not*/
inline bool check_messages(std::string const & s1, std::string const & s2)
{
  bool const msg_ok(is_substring_of(s1, s2));
  if (!msg_ok) {
    printf("%s:%i expected: %s\n", __FUNCTION__, __LINE__, s1.c_str());
    printf("%s:%i actual: %s\n", __FUNCTION__, __LINE__, s2.c_str());
  }
  return msg_ok;
} // check_messages

TEST(dbc_notify, OneOf){
  std::string key("Key1");
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try{
    std::set<std::string> set1{key,"Key2","something else"};
    bool retval1 = OneOf(key,set1);
    EXPECT_TRUE(retval1);
    // clang-format off
    std::set<std::string> set2{"Key3","something completely different"};
    fail_line = __LINE__; bool retval2 = OneOf(key,set2);
    // clang-format on
    EXPECT_FALSE(retval2);
    std::string fail_msg(outs.str());
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'key not in set' failed";
    EXPECT_TRUE(check_messages(exp_msg.str(), fail_msg));
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false); // should not get here!
  }
  restore_stream();
} // TEST(dbc_notify, OneOf)

TEST(dbc_notify, Equal)
{
  int i = 1;
  int j = 2;
  int k = 1;
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try {
    bool ret_val(true);
    ret_val = Equal(i, k);
    EXPECT_TRUE(ret_val); // clang-format off
    fail_line = __LINE__;ret_val = Equal(i,j);
    // clang-format on
    EXPECT_FALSE(ret_val);
    std::string fail_msg(outs.str());
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'i != j' failed";
    EXPECT_TRUE(check_messages(exp_msg.str(), fail_msg));
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false); // shouldn't get here!
  }
  restore_stream();
} // TEST(dbc,Equal){

TEST(dbc_notify, NotEqual)
{
  int i = 1;
  int j = 2;
  int k = 1;
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try {
    bool ret_val(true);
    ret_val = NotEqual(i, j);
    EXPECT_TRUE(ret_val); // clang-format off
    fail_line = __LINE__;ret_val = NotEqual(i,k);
    // clang-format on
    EXPECT_FALSE(ret_val);
    std::string fail_msg(outs.str());
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'i expected != k' failed";
    EXPECT_TRUE(check_messages(exp_msg.str(), fail_msg));
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false); // shouldn't get here!
  }
  restore_stream();
} // TEST(dbc,NotEqual){

TEST(dbc_notify, InOpenRange)
{
  int i = 1;
  int j = 2;
  int k = 4;
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try {
    bool ret_val(true);
    ret_val = InOpenRange(j, i, k);
    EXPECT_TRUE(ret_val); // clang-format off
    fail_line = __LINE__;ret_val = InOpenRange(i,j,k);
    // clang-format on
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'i (1) was not in range (2,4)' failed";
    std::string excmsg(outs.str());
    EXPECT_TRUE(check_messages(exp_msg.str(), excmsg));
    /* Should not get here with exceptions*/
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false);
  }
  restore_stream();
} // TEST(dbc,InOpenRange){

TEST(dbc_notify, Insist)
{
  int i = 1;
  int j = 2;
  int k = 4;
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try { // clang-format off
    fail_line = __LINE__; Insist(i == j, "i == j"); // clang-format on
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'i == j' failed";
    std::string excmsg(outs.str());
    EXPECT_TRUE(check_messages(exp_msg.str(), excmsg));
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false);
  }
  restore_stream();
} // TEST(dbc,InOpenRange){

TEST(dbc_notify, LessThan)
{
  int i = 1;
  int j = 2;
  int k = 4;
  int fail_line = -1;
  std::stringstream outs;
  divert_stream(&outs);
  try {
    bool ret_val = LessThan(i, j);
    EXPECT_TRUE(ret_val);
    // clang-format off
    fail_line = __LINE__;ret_val = LessThan(j, i);
    // clang-format on
    std::stringstream exp_msg;
    exp_msg << __FILE__ << ":" << fail_line
            << ":TestBody assertion 'j (2) >= 1' failed";
    std::string excmsg(outs.str());
    EXPECT_TRUE(check_messages(exp_msg.str(), excmsg));
  } catch (std::exception & e) {
    printf("%s:%i: With DBC notify enabled, no exception should be thrown!!\n",
      __FUNCTION__, __LINE__);
    EXPECT_TRUE(false);
  }
  restore_stream();
} // TEST(dbc,InOpenRange){

// End of file
