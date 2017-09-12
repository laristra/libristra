// test-announce.cc
// T. M. Kelley
// Aug 17, 2017
// (c) Copyright 2017 LANSLLC, all rights reserved

#include "ristra/type_traits.h"
#include "cinchtest.h"

struct A{
  template <class T, typename std::enable_if<std::is_function<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "is_function";
  }

  template <class T, typename std::enable_if<!std::is_function<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "isnt_function";
  }
}; // struct A

struct B{
  template <class T,
    typename std::enable_if<ristra::is_callable<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "is_callable";
  }

  template <class T,
    typename std::enable_if<!ristra::is_callable<T>::value, int>::type = 0>
  std::string try_me()
  {
    return "isnt_callable";
  }
}; // struct B

class C{
public:
  std::string operator()(){return "boo-ya!!";}
}; // class C

// some types
auto f2 = [](int x){return x + 1;};

using t1 = std::function<std::tuple<double,double>(double,int)>;
using t2 = decltype(f2);
using t3 = std::vector<int>;
using t4 = uint32_t;
using t5 = C;

TEST(type_traits,callable){
  {
    A a;

    std::string result1 = a.try_me<t1>();
    EXPECT_EQ(result1,"isnt_function");

    std::string result2 = a.try_me<t2>();
    EXPECT_EQ(result2,"isnt_function");

    std::string result3 = a.try_me<t3>();
    EXPECT_EQ(result3,"isnt_function");

    std::string result4 = a.try_me<t4>();
    EXPECT_EQ(result4,"isnt_function");

    std::string result5 = a.try_me<t5>();
    EXPECT_EQ(result5,"isnt_function");
  }
  {
    B b;

    std::string result1 = b.try_me<t1>();
    EXPECT_EQ(result1,"is_callable");

    std::string result2 = b.try_me<t2>();
    EXPECT_EQ(result2,"is_callable");

    std::string result5 = b.try_me<t5>();
    EXPECT_EQ(result5,"is_callable");

    std::string result3 = b.try_me<t3>();
    EXPECT_EQ(result3,"isnt_callable");

    std::string result4 = b.try_me<t4>();
    EXPECT_EQ(result4,"isnt_callable");
  }
}

// End of file
