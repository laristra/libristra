/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to the matrix class.
///////////////////////////////////////////////////////////////////////////////

#include<ristra/ristra-config.h>

// user includes
#include "ristra/math/matrix.h"

// system includes
#include <gtest/gtest.h>
#include <iostream>
#include <cmath>

// explicitly use some stuff
using namespace ristra;
using namespace ristra::math;

using real_t = config::real_t;
using matrix_1d_t = matrix<real_t,1,1>;
using matrix_2d_t = matrix<real_t,2,3>;



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the intialization.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, init) {

  auto strides1 = math::multi_array<real_t,2,3>::strides();
  std::cout << strides1[0] << " " << strides1[1] << " " << std::endl;

  auto strides2 = math::multi_array<real_t,2,3,4>::strides();
  std::cout << strides2[0] << " " << strides2[1] << " " << strides2[2] << std::endl;

  auto shape = matrix_2d_t::shape();
  std::cout << matrix_2d_t::element( 0, 0 ) << " " << matrix_2d_t::element( 0, 1 ) << " " << matrix_2d_t::element( 1, 0 ) << std::endl;

  // { 1.0 }
  matrix_1d_t ans_1d{ 1.0 };
  //matrix_1d_t a1( 1.0 );    ASSERT_TRUE( a1 == ans_1d );
  matrix_1d_t a2{ 1.0 };    ASSERT_TRUE( a2 == ans_1d );
  //matrix_1d_t a3 = 1.0;     ASSERT_TRUE( a3 == ans_1d );
  matrix_1d_t a4 = { 1.0 }; ASSERT_TRUE( a4 == ans_1d );
  matrix_1d_t a5 = a4;
  matrix_1d_t a6( a4 );
  a4.fill( 6.0 );
  ASSERT_TRUE( a5 == ans_1d );
  ASSERT_TRUE( a6 == ans_1d );
  matrix_1d_t a7( 1.0 ); ASSERT_TRUE( a7 == ans_1d );

  // { 1.0, 2.0 }
  matrix_2d_t ans_2d{ 1.0, 2.0, 3.0,
                      3.0, 2.0, 1.0 };
  
  matrix_2d_t b2{ { 1.0, 2.0, 3.0,
                    3.0, 2.0, 1.0 } };      
  ASSERT_TRUE( b2 == ans_2d );
  
  matrix_2d_t b3( b2 );            
  ASSERT_TRUE( b3 == ans_2d );
  
  matrix_2d_t b4 = { 1.0, 2.0, 3.0,
                     3.0, 2.0, 1.0 };     
  ASSERT_TRUE( b4 == ans_2d );

  matrix_2d_t b5; 
  b5 = { 1.0, 1.0, 3.0,
         3.0, 2.0, 1.0 }; 
  ASSERT_FALSE( b5 == ans_2d );
  
  b5 = { 1.0, 2.0, 3.0,
         3.0, 2.0, 1.0 }; 
  ASSERT_TRUE ( b5 == ans_2d );

  // { 1.0, 1.0 }
  //ans_2d = { 1.0, 1.0 };
  //matrix_2d_t b6( 1.0 );    ASSERT_TRUE( b6 == ans_2d );
  //matrix_2d_t b7{ 1.0 };    ASSERT_TRUE( b7 == ans_2d );
  //matrix_2d_t b8 = {1.0};   ASSERT_TRUE( b8 == 1.0 );
 
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the addition of a one-by-one matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, addition_1d) {

  // { 1.0 } + { 2.0 } = { 3.0 }
  matrix_1d_t ans{ 3.0 }; 
  matrix_1d_t a{ 1.0 };
  matrix_1d_t b{ 2.0 };

  auto c = a;
  c += b ;
  ASSERT_TRUE( c == ans ) << " error in += with matrix";

  auto d = a + b; 
  ASSERT_TRUE( d == ans ) << " error in operator+ with matrix";

  // { 1.0 } + 2.0 = { 3.0 }
  ans = { 3.0 };
  real_t val = 2.0;

  auto e = a;
  e += val; 
  ASSERT_TRUE( e == ans ) << " error in += with matrix";

  auto f = a + val; 
  ASSERT_TRUE( f == ans ) << " error in operator+ with scalar";
  
  // 2.0 + { 1.0 } = { 3.0 }
  auto g = val + a; 
  ASSERT_TRUE( g == ans ) << " error in operator+ with scalar";
  

}



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the addition of a two-by-three matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, addition_2d) {


  // { 1.0, 2.0 } + { 2.0, 1.0 } = { 3.0, 3.0 }
  matrix_2d_t a{ 1.0, 2.0, 0.0, 
                 1.0, 2.0, 0.0 };
  matrix_2d_t b{ 2.0, 1.0, 0.0,
                 2.0, 1.0, 0.0 };
  matrix_2d_t ans{ 3.0, 3.0, 0.0,
                   3.0, 3.0, 0.0 };

  auto c = a;
  c += b;
  ASSERT_TRUE( c == ans ) << " error in operator+= with matrix";
  
  auto d = a + b; 
  ASSERT_TRUE( d == ans ) << " error in operator+ with matrix";

  // { 1.0, 2.0 } + 2.0 = { 3.0, 4.0 }
  ans = { 3.0, 4.0, 2.0,
          3.0, 4.0, 2.0 };
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
//! \brief Test the subtraction of a one-by-one matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, subtraction_1d) {

  // { 1.0 } - { 2.0 } = { -1.0 }
  matrix_1d_t ans{ -1.0 }; 
  matrix_1d_t a{ 1.0 };
  matrix_1d_t b{ 2.0 };

  auto c = a;
  c -= b;
  ASSERT_TRUE( c == ans ) << " error in operator-= with matrix";
  
  auto d = a - b; 
  ASSERT_TRUE( d == ans ) << " error in operator- with matrix";

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
//! \brief Test the subtraction of a two-by-three matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, subtraction_2d) {


  // { 1.0, 2.0 } - { 2.0, 1.0 } = { -1.0, 1.0 }
  matrix_2d_t a{ 1.0, 2.0, 0.0,
                 1.0, 2.0, 0.0 };
  matrix_2d_t b{ 2.0, 1.0, 0.0,
                 2.0, 1.0, 0.0 };
  matrix_2d_t ans{ -1.0, 1.0, 0.0,
                   -1.0, 1.0, 0.0 };

  auto c = a;
  c -= b;
  ASSERT_TRUE( c == ans ) << " error in operator-= with matrix";
  
  auto d = a - b; 
  ASSERT_TRUE( d == ans ) << " error in operator- with matrix";

  // { 1.0, 2.0 } - 2.0 = { -1.0, 0.0 }
  ans = { -1.0, 0.0, -2.0,
          -1.0, 0.0, -2.0 };
  real_t val = 2.0;

  auto e = a;
  e -= val;
  ASSERT_TRUE( e == ans ) << " error in operator-= with scalar";
  
  auto f = a - val; 
  ASSERT_TRUE( f == ans ) << " error in operator- with scalar";
   
  // 2.0 - { 1.0, 2.0 } = { 1.0, 0.0 }
  ans = { 1.0, 0.0, 2.0,
          1.0, 0.0, 2.0 };

  auto g = val - a; 
  ASSERT_TRUE( g == ans ) << " error in operator- with scalar";

}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the multiplication of a one-by-one matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, multiply_1d) {

  // { 2.0 } * { 6.0 } = { 6.0 }
  matrix_1d_t ans{ 6.0 }; 
  matrix_1d_t a{ 2.0 };
  matrix_1d_t b{ 3.0 };

  auto c = a;
  c *= b;
  ASSERT_TRUE( c == ans ) << " error in operator*= with matrix";
  
  auto d = a * b; 
  ASSERT_TRUE( d == ans ) << " error in operator* with matrix";

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
//! \brief Test the multiplication of a two-by-three matrix..
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, multiply_2d) {


  // { 2.0, 3.0 } + { 3.0, 2.0 } = { 6.0, 6.0 }
  matrix_2d_t a{ 2.0, 3.0, 0.0,
                 2.0, 3.0, 0.0 };
  matrix_2d_t b{ 3.0, 2.0, 0.0,
                 3.0, 2.0, 0.0 };
  matrix_2d_t ans{ 6.0, 6.0, 0.0,
                   6.0, 6.0, 0.0 };

  auto c = a;
  c *= b;
  ASSERT_TRUE( c == ans ) << " error in operator*= with matrix";
  
  auto d = a * b; 
  ASSERT_TRUE( d == ans ) << " error in operator* with matrix";

  // { 2.0, 3.0 } * 2.0 = { 4.0, 6.0 }
  ans = { 4.0, 6.0, 0.0,
          4.0, 6.0, 0.0 };
  real_t val = 2.0;

  auto e = a;
  e *= val;
  ASSERT_TRUE( e == ans ) << " error in operator*= with scalar";
  
  auto f = a * val; 
  ASSERT_TRUE( f == ans ) << " error in operator* with scalar";

  // 3.0 * { 2.0, 3.0 } = { 4.0, 6.0 }
  ans = { 4.0, 6.0, 0.0,
          4.0, 6.0, 0.0 };

  auto g = val * a; 
  ASSERT_TRUE( g == ans ) << " error in operator* with scalar";
 
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the division of a one-by-one matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, divide_1d) {

  // { 6.0 } / { 2.0 } = { 3.0 }
  matrix_1d_t ans{ 3.0 }; 
  matrix_1d_t a{ 6.0 };
  matrix_1d_t b{ 2.0 };

  auto c = a;
  c /= b;
  ASSERT_TRUE( c == ans ) << " error in operator/= with matrix";
  
  auto d = a / b; 
  ASSERT_TRUE( d == ans ) << " error in operator/ with matrix";

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
//! \brief Test the division of a two-by-three matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, divide_2d) {


  // { 12.0, 12.0 } / { 3.0, 2.0 } = { 8.0, 6.0 }
  matrix_2d_t a{ 24.0, 12.0, 1.0,
                 24.0, 12.0, 1.0 };
  matrix_2d_t b{ 3.0, 2.0, 1.0,
                 3.0, 2.0, 1.0 };
  matrix_2d_t ans{ 8.0, 6.0, 1.0,
                   8.0, 6.0, 1.0 };

  auto c = a;
  c /= b;
  ASSERT_TRUE( c == ans ) << " error in operator/= with matrix";
  
  auto d = a / b; 
  ASSERT_TRUE( d == ans ) << " error in operator/ with matrix";

  // { 24.0, 12.0 } / 2.0 = { 12.0, 6.0 }
  ans = { 12.0, 6.0, 0.5, 
          12.0, 6.0, 0.5 };
  real_t val = 2.0;

  auto e = a;
  e /= val;
  ASSERT_TRUE( e == ans ) << " error in operator/= with scalar";
  
  auto f = a / val; 
  ASSERT_TRUE( f == ans ) << " error in operator/ with scalar";

  // 48.0 / { 24.0, 12.0 } = { 2.0, 4.0 }
  ans = { 2.0, 4.0, 48.0,
          2.0, 4.0, 48.0 };
  val = 48.0;

  auto g = val / a; 
  ASSERT_TRUE( g == ans ) << " error in operator/ with scalar";
 
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the inverse of a one-by-one matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, invert_1d) {

  matrix<real_t,1,1> a{ 4.0 };
  matrix<real_t,1,1> ans{ 0.25 }; 

  auto ainv = inverse(a);
  ASSERT_TRUE( ainv == ans ) << " error in inverse(matrix)";
  
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the inverse of a two-by-two matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, invert_2d) {

  matrix<real_t,2,2> a{ 1.0, 2.0, 3.0, 4.0 };
  matrix<real_t,2,2> ans{ -2.0, 1.0, 1.5, -0.5 };

  auto ainv = inverse(a);
  ASSERT_TRUE( ainv == ans ) << " error in inverse(matrix)";
  
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the inverse of a two-by-two matrix.
///////////////////////////////////////////////////////////////////////////////
TEST(matrix, invert_5d) {

  matrix<real_t,5,5> a{
    1.0, 0.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 0.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 0.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 0.0,
    1.0, 1.0, 1.0, 1.0, 1.0
  };
  matrix<real_t,5,5> ans{
    1.0, 0.0, 0.0, 0.0, 0.0,
   -1.0, 1.0, 0.0, 0.0, 0.0,
    0.0,-1.0, 1.0, 0.0, 0.0,
    0.0, 0.0,-1.0, 1.0, 0.0,
    0.0, 0.0, 0.0,-1.0, 1.0
  };

  std::cout <<"STARTING" << std::endl;
  auto ainv = inverse(a);
  ASSERT_TRUE( ainv == ans ) << " error in inverse(matrix)";
  
}

