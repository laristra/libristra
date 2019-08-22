// test-announce.cc
// T. M. Kelley
// Aug 17, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include "ristra/utils/type_traits.h"
#include "cinchtest.h"

// some containers that yeild interesting types
#include <array>
#include <map>
#include <memory>
#include <vector>

using namespace ristra::utils;

struct A {
  template <class T,
    typename std::enable_if<std::is_function<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "is_function";
  }

  template <class T,
    typename std::enable_if<!std::is_function<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "isnt_function";
  }
}; // struct A

struct B {
  template <class T,
    typename std::enable_if<is_callable<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "is_callable";
  }

  template <class T,
    typename std::enable_if<!is_callable<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "isnt_callable";
  }
}; // struct B

class C
{
 public:
  std::string operator()() { return "boo-ya!!"; }
}; // class C

template <template <class...> class trait_t, typename... Ts>
struct tester {
  static constexpr bool value = trait_t<Ts...>::value;
};

// some types
auto f2 = [](int x) { return x + 1; };

using t1 = std::function<std::tuple<double, double>(double, int)>;
using t2 = decltype(f2);
using t3 = std::vector<int>;
using t4 = uint32_t;
using t5 = C;

TEST(type_traits, callable)
{
  {
    A a;

    std::string result1 = a.try_me<t1>();
    EXPECT_EQ(result1, "isnt_function");

    std::string result2 = a.try_me<t2>();
    EXPECT_EQ(result2, "isnt_function");

    std::string result3 = a.try_me<t3>();
    EXPECT_EQ(result3, "isnt_function");

    std::string result4 = a.try_me<t4>();
    EXPECT_EQ(result4, "isnt_function");

    std::string result5 = a.try_me<t5>();
    EXPECT_EQ(result5, "isnt_function");
  }
  {
    B b;

    std::string result1 = b.try_me<t1>();
    EXPECT_EQ(result1, "is_callable");

    std::string result2 = b.try_me<t2>();
    EXPECT_EQ(result2, "is_callable");

    std::string result5 = b.try_me<t5>();
    EXPECT_EQ(result5, "is_callable");

    std::string result3 = b.try_me<t3>();
    EXPECT_EQ(result3, "isnt_callable");

    std::string result4 = b.try_me<t4>();
    EXPECT_EQ(result4, "isnt_callable");
  }
} // TEST(type_traits,callable)

using t6 = std::array<double, 2>;
using t7 = std::map<std::string, std::string>;

TEST(type_traits, has_call_operator)
{
  bool const case1_ok = has_call_operator<t1, double, int>::value;
  EXPECT_TRUE(case1_ok);

  bool const case2_ok =
    has_call_operator<t1, double, std::string>::value;
  EXPECT_FALSE(case2_ok);

  bool const case3_ok = has_call_operator<t6, double, double>::value;
  EXPECT_FALSE(case3_ok);

  bool const case4_ok = has_call_operator<t4>::value;
  EXPECT_FALSE(case4_ok);
}

TEST(type_traits, subscriptable)
{
  bool const case1_ok = tester<is_callable, t1>::value;
  EXPECT_TRUE(case1_ok);

  bool const case2_ok = has_subscript_operator<t6, size_t>::value;
  EXPECT_TRUE(case2_ok);

  bool const case3_ok = has_subscript_operator<t6, int>::value;
  EXPECT_TRUE(case3_ok);

  bool const case4_ok = has_subscript_operator<C, int>::value;
  EXPECT_FALSE(case4_ok);

  bool const case5_ok = has_subscript_operator<t2, int>::value;
  EXPECT_FALSE(case5_ok);

  bool const case6_ok = has_subscript_operator<t3, int>::value;
  EXPECT_TRUE(case6_ok);

  bool const case7_ok = has_subscript_operator<t4, int>::value;
  EXPECT_FALSE(case7_ok);

  bool const case8_ok = has_subscript_operator<t7, std::string>::value;
  EXPECT_TRUE(case8_ok);

  bool const case9_ok = has_subscript_operator<t7, int>::value;
  EXPECT_FALSE(case9_ok);

} // TEST(type_traits,subscriptable)

///////////////////////////////////////////////////////////////////////////////
// Tests of is_iterator
///////////////////////////////////////////////////////////////////////////////
TEST(type_traits, is_iterator){
  std::vector<int> v;
  constexpr bool case1_result = is_iterator_v<decltype(v.begin())>;
  EXPECT_TRUE(case1_result);

  constexpr bool case2_result = is_iterator_v<int>;
  EXPECT_FALSE(case2_result);

  // a pointer can be used with any iterator algorithm
  constexpr bool case3_result = is_iterator_v<int *>;
  EXPECT_TRUE(case3_result);

  // a shared pointer cannot be used with any iterator algorithm
  constexpr bool case4_result = is_iterator_v<std::shared_ptr<int>>;
  EXPECT_FALSE(case4_result);
} // TEST(type_traits, is_iterator){



///////////////////////////////////////////////////////////////////////////////
// Tests of is_ostream_writeable
///////////////////////////////////////////////////////////////////////////////


struct Foo{};

struct Zoo{
  friend std::ostream & operator<<(std::ostream & s, Zoo const &) { return s; }
};

TEST(type_traits, is_ostream_writeable)
{
  bool constexpr case1_result = is_ostream_writeable<int>();
  EXPECT_TRUE(case1_result);

  bool constexpr case2_result = is_ostream_writeable<Foo>();
  EXPECT_FALSE(case2_result);

  bool constexpr case3_result = is_ostream_writeable<Zoo>();
  EXPECT_TRUE(case3_result);

} // TEST(type_traits, is_ostream_writeable)

// End of file
