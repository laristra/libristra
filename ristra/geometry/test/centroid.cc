/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
/// 
/// \brief Tests related to the centroid operation.
///
////////////////////////////////////////////////////////////////////////////////

// test includes
#include <cinchtest.h>
#include <ristra-config.h>

// user includes
#include <ristra/geometry/centroid.h>
#include <ristra/geometry/point.h>

// system includes
#include<vector>

// explicitly use some stuff
using std::cout;
using std::endl;
using std::vector;

using namespace ristra;
using namespace ristra::geometry;

//! the real type
using real_t = config::real_t;
// ! the test tolerance
using config::test_tolerance;

//! the point type
using point_2d_t = point<real_t, 2>;

//=============================================================================
//! \brief Test centroid operator.
//=============================================================================
TEST(centroid, 2d) 
{

  vector<point_2d_t> points = { {0, 0}, {1, 0}, {1, 1}, {0, 1} };
  
  auto cx1 = centroid( 
    point_2d_t{0, 0}, point_2d_t{1, 0}, point_2d_t{1, 1}, point_2d_t{0, 1} 
  );
  auto cx2 = centroid( points );

  ASSERT_NEAR( 0.5, cx1[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 0.5, cx2[0], test_tolerance ) << " Centroid calculation wrong ";

  ASSERT_NEAR( 0.5, cx1[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 0.5, cx2[1], test_tolerance ) << " Centroid calculation wrong ";

} // TEST
