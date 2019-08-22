/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to the computational geometry for different shapes.
////////////////////////////////////////////////////////////////////////////////

// the main test include
#include <gtest/gtest.h>
#include <ristra-config.h>

// user includes
#include <ristra/geometry/shapes/hexahedron.h>
#include <ristra/geometry/shapes/quadrilateral.h>
#include <ristra/geometry/shapes/polyhedron.h>
#include <ristra/geometry/shapes/polygon.h>
#include <ristra/geometry/shapes/tetrahedron.h>
#include <ristra/geometry/shapes/triangle.h>
#include <ristra/math/constants.h>
#include <ristra/math/matrix.h>
#include <ristra/math/vector.h>


// system includes
#include<array>
#include<vector>

// explicitly use some stuff
using std::cout;
using std::endl;
using std::vector;

using namespace ristra;
using namespace ristra::geometry::shapes;

//! the real type
using real_t = config::real_t;
// ! the test tolerance
using config::test_tolerance;

//! the point type
using point_2d_t = math::vector<real_t, 2>;
using point_3d_t = math::vector<real_t, 3>;


///////////////////////////////////////////////////////////////////////////////
//! \brief create a rotation matrix 
///////////////////////////////////////////////////////////////////////////////
auto rotation_matrix_y( real_t radians ) 
{

  // the trig functions
  auto cos = std::cos( radians );
  auto sin = std::sin( radians );
  
  // create a rotation matrix
  math::matrix< real_t, 3, 3 > rot;

  rot(0, 0) = cos;
  rot(0, 1) = 0;
  rot(0, 2) = sin;

  rot(1, 0) = 0;
  rot(1, 1) = 1;
  rot(1, 2) = 0;

  rot(2, 0) = -sin;
  rot(2, 1) = 0;
  rot(2, 2) = cos;

  return rot;

}

///////////////////////////////////////////////////////////////////////////////
//! \brief Test triangle operations
//! \remark 2d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, triangle_2d) 
{

  auto pt0 = point_2d_t{0, 0};
  auto pt1 = point_2d_t{1, 0};
  auto pt2 = point_2d_t{0, 1};

  auto area = triangle<2>::area( pt0, pt1, pt2 );
  auto xc = triangle<2>::centroid( pt0, pt1, pt2 );

  ASSERT_NEAR(   0.5, area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( 1./3., xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 1./3., xc[1], test_tolerance ) << " Centroid calculation wrong ";

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test triangle operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, triangle_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{0, 1, 0 };

  // the centroid answer
  auto xc_ans = point_3d_t{ 1./3., 1./3., 0 };
  auto n_ans = point_3d_t{ 0, 0, 0.5 };
  auto area_ans = 0.5;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  // transform the coords
  pt0 = rot * pt0;
  pt1 = rot * pt1;
  pt2 = rot * pt2;
  xc_ans = rot * xc_ans;
  n_ans = rot * n_ans;

  auto area = triangle<3>::area( pt0, pt1, pt2 );
  auto xc = triangle<3>::centroid( pt0, pt1, pt2 );
  auto n  = triangle<3>::normal( pt0, pt1, pt2 );

  ASSERT_NEAR(  area_ans, area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR(  n_ans[0],  n[0], test_tolerance ) << " normal calculation wrong ";
  ASSERT_NEAR(  n_ans[1],  n[1], test_tolerance ) << " normal calculation wrong ";
  ASSERT_NEAR(  n_ans[2],  n[2], test_tolerance ) << " normal calculation wrong ";

} // TEST



///////////////////////////////////////////////////////////////////////////////
//! \brief Test quadrilateral operations
//! \remark 2d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, quadrilateral_2d) 
{

  auto pt0 = point_2d_t{0, 0};
  auto pt1 = point_2d_t{1, 0};
  auto pt2 = point_2d_t{1, 1};
  auto pt3 = point_2d_t{0, 1};

  auto area = quadrilateral<2>::area( pt0, pt1, pt2, pt3 );
  auto xc = quadrilateral<2>::centroid( pt0, pt1, pt2, pt3 );

  ASSERT_NEAR(  1., area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( 0.5, xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 0.5, xc[1], test_tolerance ) << " Centroid calculation wrong ";

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test quadrilateral operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, quadrilateral_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{1, 1, 0 };
  auto pt3 = point_3d_t{0, 1, 0 };

  // the centroid answer
  auto xc_ans = point_3d_t{ 0.5, 0.5, 0 };
  auto n_ans = point_3d_t{ 0, 0, 1 };
  auto area_ans = 1.0;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  // transform the coords
  pt0 = rot * pt0;
  pt1 = rot * pt1;
  pt2 = rot * pt2;
  xc_ans = rot * xc_ans;
  n_ans = rot * n_ans;

  auto area = quadrilateral<3>::area( pt0, pt1, pt2, pt3 );
  auto xc = quadrilateral<3>::centroid( pt0, pt1, pt2, pt3 );
  auto n = quadrilateral<3>::normal( pt0, pt1, pt2, pt3 );

  ASSERT_NEAR(  area_ans, area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR(  n_ans[0],  n[0], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[1],  n[1], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[2],  n[2], test_tolerance ) << " Normal calculation wrong ";

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test polygon operations
//! \remark 2d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, polygon_2d) 
{

  auto pt0 = point_2d_t{0, 0};
  auto pt1 = point_2d_t{1, 0};
  auto pt2 = point_2d_t{1, 1};
  auto pt3 = point_2d_t{0, 1};

  auto points = std::vector<point_2d_t>{pt0, pt1, pt2, pt3};

  auto area = polygon<2>::area( pt0, pt1, pt2, pt3 );
  auto xc = polygon<2>::centroid( pt0, pt1, pt2, pt3 );

  ASSERT_NEAR(  1., area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( 0.5, xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 0.5, xc[1], test_tolerance ) << " Centroid calculation wrong ";

  area = polygon<2>::area( points );
  xc = polygon<2>::centroid( points );

  ASSERT_NEAR(  1., area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( 0.5, xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( 0.5, xc[1], test_tolerance ) << " Centroid calculation wrong ";

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test polygon operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, polygon_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{1, 1, 0 };
  auto pt3 = point_3d_t{0, 1, 0 };

  // the centroid answer
  auto xc_ans = point_3d_t{ 0.5, 0.5, 0 };
  auto n_ans = point_3d_t{ 0, 0, 1 };
  auto area_ans = 1.0;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  // transform the coords
  pt0 = rot * pt0;
  pt1 = rot * pt1;
  pt2 = rot * pt2;
  xc_ans = rot * xc_ans;
  n_ans = rot * n_ans;

  auto points = std::vector<point_3d_t>{pt0, pt1, pt2, pt3};

  auto area = polygon<3>::area( pt0, pt1, pt2, pt3 );
  auto xc = polygon<3>::centroid( pt0, pt1, pt2, pt3 );
  auto n = polygon<3>::normal( pt0, pt1, pt2, pt3 );

  ASSERT_NEAR(  area_ans, area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR(  n_ans[0],  n[0], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[1],  n[1], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[2],  n[2], test_tolerance ) << " Normal calculation wrong ";

  area = polygon<3>::area( points );
  xc = polygon<3>::centroid( points );
  n = polygon<3>::normal( points );

  ASSERT_NEAR(  area_ans, area, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR(  n_ans[0],  n[0], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[1],  n[1], test_tolerance ) << " Normal calculation wrong ";
  ASSERT_NEAR(  n_ans[2],  n[2], test_tolerance ) << " Normal calculation wrong ";

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test tetrahedron operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, tetrahedron_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{0, 1, 0 };
  auto pt3 = point_3d_t{0, 0, 1 };

  // the centroid answer
  auto xc_ans = point_3d_t{ 1./4., 1./4., 1./4. };
  auto vol_ans = 1. / 6.;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  auto vol = tetrahedron::volume( pt0, pt1, pt2, pt3 );
  auto xc = tetrahedron::centroid( pt0, pt1, pt2, pt3 );

  ASSERT_NEAR(   vol_ans,   vol, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test hexahedron operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, hexahedron_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{1, 1, 0 };
  auto pt3 = point_3d_t{0, 1, 0 };
  auto pt4 = point_3d_t{0, 0, 1 };
  auto pt5 = point_3d_t{1, 0, 1 };
  auto pt6 = point_3d_t{1, 1, 1 };
  auto pt7 = point_3d_t{0, 1, 1 };

  // the centroid answer
  auto xc_ans = point_3d_t{ 0.5, 0.5, 0.5 };
  auto vol_ans = 1.;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  auto vol = hexahedron::volume( pt0, pt1, pt2, pt3, pt4, pt5, pt6, pt7 );
  auto xc = hexahedron::centroid( pt0, pt1, pt2, pt3, pt4, pt5, pt6, pt7 );

  ASSERT_NEAR(   vol_ans,   vol, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";

} // TEST



///////////////////////////////////////////////////////////////////////////////
//! \brief Test polyhedron operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, polyhedron_3d) 
{

  // original points
  auto pt0 = point_3d_t{0, 0, 0 };
  auto pt1 = point_3d_t{1, 0, 0 };
  auto pt2 = point_3d_t{1, 1, 0 };
  auto pt3 = point_3d_t{0, 1, 0 };
  auto pt4 = point_3d_t{0, 0, 1 };
  auto pt5 = point_3d_t{1, 0, 1 };
  auto pt6 = point_3d_t{1, 1, 1 };
  auto pt7 = point_3d_t{0, 1, 1 };

  using polyhedron = polyhedron< point_3d_t >;

  polyhedron poly;
  poly.insert( {pt0, pt1, pt2, pt3} );
  poly.insert( {pt4, pt7, pt6, pt5} );
  poly.insert( {pt0, pt4, pt5, pt1} );
  poly.insert( {pt1, pt5, pt6, pt2} );
  poly.insert( {pt2, pt6, pt7, pt3} );
  poly.insert( {pt3, pt7, pt4, pt0} );

  // the centroid answer
  auto xc_ans = point_3d_t{ 0.5, 0.5, 0.5 };
  auto vol_ans = 1.;
  
  // compute some angles
  auto degrees = 45;
  auto radians = degrees * math::pi / 180;
  auto rot = rotation_matrix_y( radians );

  auto vol = poly.volume();
  auto xc = poly.centroid();

  ASSERT_NEAR(   vol_ans,   vol, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test polyhedron operations
//! \remark 3d version
///////////////////////////////////////////////////////////////////////////////
TEST(shapes, compare_3d) 
{
  // original points
  auto pt0 = point_3d_t{ -0.5,  -0.5,  0.25 };
  auto pt1 = point_3d_t{ -0.5,  -0.5,  0 };
  auto pt2 = point_3d_t{ -0.5,  -0.25, 0 };
  auto pt3 = point_3d_t{ -0.5,  -0.25, 0.25 };
  auto pt4 = point_3d_t{ -0.25, -0.5,  0.25 };
  auto pt5 = point_3d_t{ -0.25, -0.5,  0 };
  auto pt6 = point_3d_t{ -0.25, -0.25, 0 };
  auto pt7 = point_3d_t{ -0.25, -0.25, 0.25 };

  // the centroid answer
  auto xc_ans = point_3d_t{ -0.375, -0.375, 0.125 };
  auto vol_ans = 0.015625;
  
  // compute some angles
  auto vol = hexahedron::volume( pt0, pt1, pt2, pt3, pt4, pt5, pt6, pt7 );
  auto xc = hexahedron::centroid( pt0, pt1, pt2, pt3, pt4, pt5, pt6, pt7 );

  ASSERT_NEAR(   vol_ans,   vol, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";

  // now build the polyhedron
  pt0 = point_3d_t{ -0.5,  -0.25, 0.25 };
  pt1 = point_3d_t{ -0.5,  -0.25, 0 };
  pt2 = point_3d_t{ -0.5,  -0.5,  0 };
  pt3 = point_3d_t{ -0.5,  -0.5,  0.25 };
  pt4 = point_3d_t{ -0.25, -0.5,  0 };
  pt5 = point_3d_t{ -0.25, -0.25, 0 };
  pt6 = point_3d_t{ -0.25, -0.25, 0.25 };
  pt7 = point_3d_t{ -0.25, -0.5,  0.25 };

  using polyhedron = polyhedron< point_3d_t >;
  polyhedron poly;
  poly.insert( {pt0, pt1, pt2, pt3} );
  poly.insert( {pt4, pt5, pt6, pt7} );
  poly.insert( {pt2, pt4, pt7, pt3} );
  poly.insert( {pt1, pt5, pt4, pt2} );
  poly.insert( {pt0, pt6, pt5, pt1} );
  poly.insert( {pt3, pt7, pt6, pt0} );
  
  // compute some angles
  vol = poly.volume();
  xc = poly.centroid();

  ASSERT_NEAR(   vol_ans,   vol, test_tolerance ) << " Volume calculation wrong ";
  ASSERT_NEAR( xc_ans[0], xc[0], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[1], xc[1], test_tolerance ) << " Centroid calculation wrong ";
  ASSERT_NEAR( xc_ans[2], xc[2], test_tolerance ) << " Centroid calculation wrong ";

}

