/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to the vector class.
///////////////////////////////////////////////////////////////////////////////

#include<ristra-config.h>

// user includes
#include "ristra/math/general.h"
#include "ristra/math/vector.h"

// system includes
#include <cinchtest.h>
#include <iostream>

// explicitly use some stuff
using namespace ristra;
using namespace ristra::math;

using real_t = config::real_t;
using vector_1d_t = vector<real_t,1>;
using vector_2d_t = vector<real_t,2>;
using vector_3d_t = vector<real_t,3>;



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the intialization.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, init) {

  // { 1.0 }
  vector_1d_t ans_1d{ 1.0 };
  //vector_1d_t a1( 1.0 );    ASSERT_TRUE( a1 == ans_1d );
  vector_1d_t a2{ 1.0 };    ASSERT_TRUE( a2 == ans_1d );
  //vector_1d_t a3 = 1.0;     ASSERT_TRUE( a3 == ans_1d );
  vector_1d_t a4 = { 1.0 }; ASSERT_TRUE( a4 == ans_1d );
  vector_1d_t a5 = a4;
  vector_1d_t a6( a4 );
  a4.fill( 6.0 );
  ASSERT_TRUE( a5 == ans_1d );
  ASSERT_TRUE( a6 == ans_1d );

  // { 1.0, 2.0 }
  vector_2d_t ans_2d{ 1.0, 2.0 };
  //vector_2d_t b1( 1.0, 2.0 );      ASSERT_TRUE( b1 == ans_2d );
  vector_2d_t b2{ 1.0, 2.0 };      ASSERT_TRUE( b2 == ans_2d );
  vector_2d_t b3( b2 );            ASSERT_TRUE( b3 == ans_2d );
  vector_2d_t b4 = {1.0, 2.0};     ASSERT_TRUE( b4 == ans_2d );
  vector_2d_t b5; 
  b5 = {2.0, 1.0}; ASSERT_FALSE( b5 == ans_2d );
  b5 = {1.0, 2.0}; ASSERT_TRUE ( b5 == ans_2d );

  // { 1.0, 1.0 }
  //ans_2d = { 1.0, 1.0 };
  //vector_2d_t b6( 1.0 );    ASSERT_TRUE( b6 == ans_2d );
  //vector_2d_t b7{ 1.0 };    ASSERT_TRUE( b7 == ans_2d );
  //vector_2d_t b8 = {1.0};   ASSERT_TRUE( b8 == 1.0 );
 
}


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the addition.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, addition_1d) {

  // { 1.0 } + { 2.0 } = { 3.0 }
  vector_1d_t ans{ 3.0 }; 
  vector_1d_t a{ 1.0 };
  vector_1d_t b{ 2.0 };

  auto c = a;
  c += b ;
  ASSERT_TRUE( c == ans ) << " error in += with vector";

  auto d = a + b; 
  ASSERT_TRUE( d == ans ) << " error in operator+ with vector";

  // { 1.0 } + 2.0 = { 3.0 }
  ans = { 3.0 };
  real_t val = 2.0;

  auto e = a;
  e += val; 
  ASSERT_TRUE( e == ans ) << " error in += with vector";

  auto f = a + val; 
  ASSERT_TRUE( f == ans ) << " error in operator+ with scalar";
  
  // 2.0 + { 1.0 } = { 3.0 }
  auto g = val + a; 
  ASSERT_TRUE( g == ans ) << " error in operator+ with scalar";
  

}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the addition.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, addition_2d) {


  // { 1.0, 2.0 } + { 2.0, 1.0 } = { 3.0, 3.0 }
  vector_2d_t a{ 1.0, 2.0 };
  vector_2d_t b{ 2.0, 1.0 };
  vector_2d_t ans{ 3.0, 3.0 };

  auto c = a;
  c += b;
  ASSERT_TRUE( c == ans ) << " error in operator+= with vector";
  
  auto d = a + b; 
  ASSERT_TRUE( d == ans ) << " error in operator+ with vector";

  // { 1.0, 2.0 } + 2.0 = { 3.0, 4.0 }
  ans = { 3.0, 4.0 };
  real_t val = 2.0;

  auto e = a;
  e += val;
  ASSERT_TRUE( e == ans ) << " error in operator+= with scalar";
  
  auto f = a + 2.0; 
  ASSERT_TRUE( f == ans ) << " error in operator+ with scalar";

  auto g = 2.0 + a; 
  ASSERT_TRUE( g == ans ) << " error in operator+ with scalar";
 
}


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the subtraction.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, subtraction_1d) {

  // { 1.0 } - { 2.0 } = { -1.0 }
  vector_1d_t ans{ -1.0 }; 
  vector_1d_t a{ 1.0 };
  vector_1d_t b{ 2.0 };

  auto c = a;
  c -= b;
  ASSERT_TRUE( c == ans ) << " error in operator-= with vector";
  
  auto d = a - b; 
  ASSERT_TRUE( d == ans ) << " error in operator- with vector";

  // { 1.0 } - 2.0 = { -1.0 }
  ans = { -1.0 };
  real_t val = 2.0;

  auto e = a;
  e -= val;
  ASSERT_TRUE( e == ans ) << " error in operator+= with scalar";
  
  auto f = a - val; 
  ASSERT_TRUE( f == ans ) << " error in operator+ with scalar";

  // 2.0 - { 1.0 } = { 1.0 }
  ans = { 1.0 };

  auto g = val - a; 
  ASSERT_TRUE( g == ans ) << " error in operator- with scalar";  

}


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the subtraction.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, subtraction_2d) {


  // { 1.0, 2.0 } - { 2.0, 1.0 } = { -1.0, 1.0 }
  vector_2d_t a{ 1.0, 2.0 };
  vector_2d_t b{ 2.0, 1.0 };
  vector_2d_t ans{ -1.0, 1.0 };

  auto c = a;
  c -= b;
  ASSERT_TRUE( c == ans ) << " error in operator-= with vector";
  
  auto d = a - b; 
  ASSERT_TRUE( d == ans ) << " error in operator- with vector";

  // { 1.0, 2.0 } - 2.0 = { -1.0, 0.0 }
  ans = { -1.0, 0.0 };
  real_t val = 2.0;

  auto e = a;
  e -= val;
  ASSERT_TRUE( e == ans ) << " error in operator-= with scalar";
  
  auto f = a - val; 
  ASSERT_TRUE( f == ans ) << " error in operator- with scalar";
   
  // 2.0 - { 1.0, 2.0 } = { 1.0, 0.0 }
  ans = { 1.0, 0.0 };

  auto g = val - a; 
  ASSERT_TRUE( g == ans ) << " error in operator- with scalar";

}



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the multiplication.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, multiply_1d) {

  // { 2.0 } * { 6.0 } = { 6.0 }
  vector_1d_t ans{ 6.0 }; 
  vector_1d_t a{ 2.0 };
  vector_1d_t b{ 3.0 };

  auto c = a;
  c *= b;
  ASSERT_TRUE( c == ans ) << " error in operator*= with vector";
  
  auto d = a * b; 
  ASSERT_TRUE( d == ans ) << " error in operator* with vector";

  // { 2.0 } * 3.0 = { 6.0 }
  ans = { 6.0 };
  real_t val = 3.0;

  auto e = a;
  e *= val;
  ASSERT_TRUE( e == ans ) << " error in operator*= with scalar";
  
  auto f = a * val; 
  ASSERT_TRUE( f == ans ) << " error in operator* with scalar";
  
  // 3.0 * { 2.0 } = { 6.0 }
  ans = { 6.0 };

  auto g = val * a; 
  ASSERT_TRUE( g == ans ) << " error in operator* with scalar";

}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the multiplication.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, multiply_2d) {


  // { 2.0, 3.0 } + { 3.0, 2.0 } = { 6.0, 6.0 }
  vector_2d_t a{ 2.0, 3.0 };
  vector_2d_t b{ 3.0, 2.0 };
  vector_2d_t ans{ 6.0, 6.0 };

  auto c = a;
  c *= b;
  ASSERT_TRUE( c == ans ) << " error in operator*= with vector";
  
  auto d = a * b; 
  ASSERT_TRUE( d == ans ) << " error in operator* with vector";

  // { 2.0, 3.0 } * 2.0 = { 4.0, 6.0 }
  ans = { 4.0, 6.0 };
  real_t val = 2.0;

  auto e = a;
  e *= val;
  ASSERT_TRUE( e == ans ) << " error in operator*= with scalar";
  
  auto f = a * val; 
  ASSERT_TRUE( f == ans ) << " error in operator* with scalar";

  // 3.0 * { 2.0, 3.0 } = { 4.0, 6.0 }
  ans = { 4.0, 6.0 };

  auto g = val * a; 
  ASSERT_TRUE( g == ans ) << " error in operator* with scalar";
 
}



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the multiplication.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, divide_1d) {

  // { 6.0 } / { 2.0 } = { 3.0 }
  vector_1d_t ans{ 3.0 }; 
  vector_1d_t a{ 6.0 };
  vector_1d_t b{ 2.0 };

  auto c = a;
  c /= b;
  ASSERT_TRUE( c == ans ) << " error in operator/= with vector";
  
  auto d = a / b; 
  ASSERT_TRUE( d == ans ) << " error in operator/ with vector";

  // { 6.0 } / 3.0 = { 2.0 }
  ans = { 2.0 };
  real_t val = 3.0;

  auto e = a;
  e /= val;
  ASSERT_TRUE( e == ans ) << " error in operator/= with scalar";
  
  auto f = a / val; 
  ASSERT_TRUE( f == ans ) << " error in operator/ with scalar";
  
  // 12.0 / { 6.0 } = { 2.0 }
  ans = { 2.0 };
  val = 12.0;

  auto g = val / a; 
  ASSERT_TRUE( g == ans ) << " error in operator/ with scalar";

}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the multiplication.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, divide_2d) {


  // { 12.0, 12.0 } / { 3.0, 2.0 } = { 8.0, 6.0 }
  vector_2d_t a{ 24.0, 12.0 };
  vector_2d_t b{ 3.0, 2.0 };
  vector_2d_t ans{ 8.0, 6.0 };

  auto c = a;
  c /= b;
  ASSERT_TRUE( c == ans ) << " error in operator/= with vector";
  
  auto d = a / b; 
  ASSERT_TRUE( d == ans ) << " error in operator/ with vector";

  // { 24.0, 12.0 } / 2.0 = { 12.0, 6.0 }
  ans = { 12.0, 6.0 };
  real_t val = 2.0;

  auto e = a;
  e /= val;
  ASSERT_TRUE( e == ans ) << " error in operator/= with scalar";
  
  auto f = a / val; 
  ASSERT_TRUE( f == ans ) << " error in operator/ with scalar";

  // 48.0 / { 24.0, 12.0 } = { 2.0, 4.0 }
  ans = { 2.0, 4.0 };
  val = 48.0;

  auto g = val / a; 
  ASSERT_TRUE( g == ans ) << " error in operator/ with scalar";
 
}



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the dot  operator.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, dot) {
  // 1d vector dot
  vector_1d_t a1{1.0};
  vector_1d_t b1{3.0};
  ASSERT_EQ(3.0, dot_product(a1, b1));

  a1[0] = -1.0;
  ASSERT_EQ(-3.0, dot_product(a1, b1));

  // 2d vector dot
  vector_2d_t a2{1.0, 1.0};
  vector_2d_t b2{3.0, 4.0};
  ASSERT_EQ(7.0, dot_product(a2, b2));

  a2[1] = -1.0;
  ASSERT_EQ(-1.0, dot_product(a2, b2));

  // 3d vector dot
  vector_3d_t a3{1.0, 1.0, 1.0};
  vector_3d_t b3{3.0, 4.0, 5.0};
  ASSERT_EQ(12.0, dot_product(a3, b3));

  b3[2] = -5.0;
  ASSERT_EQ(2.0, dot_product(a3, b3));

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the magnitude operator.
///////////////////////////////////////////////////////////////////////////////
TEST(vector, magnitude) {

  vector_1d_t a{7.0};
  ASSERT_EQ(7.0, magnitude(a));

  a[0] = -5.0;
  ASSERT_EQ(5.0, magnitude(a));

  vector_2d_t b{3.0, 4.0};
  ASSERT_EQ(5.0, magnitude(b));

  b[1] = -4.0;
  ASSERT_EQ(5.0, magnitude(b));

  vector_3d_t c{3.0, 4.0, 5.0};
  ASSERT_EQ(sqrt(50.0), magnitude(c));

  c[2] = -5.0;
  ASSERT_EQ(sqrt(50.0), magnitude(c));

} // TEST
