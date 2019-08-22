/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/array_view.h"


// system includes
#include<gtest/gtest.h>
#include<iostream>
#include <numeric>

using namespace ristra::utils;

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the construction of strided_bounds's.
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, bounds) 
{

  strided_bounds< 1 > bounds_1d_var(1);
  strided_bounds< 1 > bounds_1d_list( {1} );

  strided_bounds< 2 > bounds_2d_var(1, 2);
  strided_bounds< 2 > bounds_2d_list( {1, 2} );
  strided_bounds< 2 > bounds_2d_copy( bounds_2d_list );

  ASSERT_EQ( bounds_2d_var, bounds_2d_list );

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the construction of index_t's.
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, index) 
{
  index_t< 1 > index_1d_var(1);
  index_t< 1 > index_1d_list( {1} );
  index_t< 1 > index_1d_copy( index_1d_list );

  index_t< 2 > index_2d_var(1, 2);
  index_t< 2 > index_2d_list( {1, 2} );
  index_t< 2 > index_2d_copy( index_2d_list );
  
  index_t< 2 > index_2d_agg1{1, 2};
  index_t< 2 > index_2d_agg2 = {1, 2};
  
  ASSERT_EQ( index_2d_var, index_2d_list );

  index_2d_copy[0] = 2;
  ASSERT_NE( index_2d_list, index_2d_copy );

  index_1d_var++;
  ASSERT_EQ( index_1d_var.at(0), 2 );

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the construction of index_t's.
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, arithmetic) 
{

  auto bnd1 = index_t<3>{ 3, 1, 4 };
  auto idx = index_t<3>{ 2, -1, 0 };
  auto  bnd2 = bnd1 + idx;  // bnd2 is { 5, 0, 4 }
  ASSERT_EQ( bnd2, index_t<3>({ 5, 0, 4 }) );
  bnd1 -= idx;  // bnd1 is { 1, 2, 4 }
  ASSERT_EQ( bnd1, index_t<3>({ 1, 2, 4 }) );

  index_t<2> idx2{ 2, 3 };
  auto res = idx2 * 2;  // res is {4, 6}
  ASSERT_EQ( res, index_t<2>({ 4, 6 }) );
 
} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the construction of array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, constructor) 
{
  auto vec = std::vector<int>(10);
  auto view = strided_array_view<int>{ vec };
  view[0] = 42;
  int v = vec[0]; // v == 42
  ASSERT_EQ( vec[0], 42 );

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  strided_array_view<int, 3> mav{ r };  // av.bounds() is {3, 1, 2}
  strided_array_view<int> fav{ mav };  // flatten multi-dimensional array

  ASSERT_EQ( mav.size(), 6 );
  
  // check ordering
  int cnt = 0;
  for ( int i=0; i<3; i++ )
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        auto a = r[i][j][k];
        auto b = mav[{i,j,k}];
        auto c = fav[cnt++];
        auto d = mav(i, j, k);
        ASSERT_EQ( a, b );
        ASSERT_EQ( a, c );
        ASSERT_EQ( a, d );
      }
  
  // check copy constructor
  strided_array_view<const int, 3> c_mav(mav);

  auto view_w_bounds_1 = strided_array_view<int,2>( vec, {2,5} );
  auto view_w_bounds_2 = strided_array_view<int,2>( vec.data(), {2,5} );

  strided_array_view<const int,2> const_view;
  const_view = view_w_bounds_1;

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the slicing array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, slice) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  strided_array_view<int, 3> mav{ r };  // av.bounds() is {3, 1, 2}
  ASSERT_EQ( mav.bounds().stride(), 2 );

  auto slice = mav.slice( 0 );
  ASSERT_EQ( slice.size(), 2 );

  // check ordering
  for ( int j=0; j<1; j++ )
    for ( int k=0; k<2; k++ ) {
      auto a = r[0][j][k];
      auto b = slice[{j,k}];
      ASSERT_EQ( a, b );
    }

  auto orig = index_t<3>({1,0,1});
  auto sec = mav.section( orig );

  for ( int i=0; i<2; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        auto new_idx = orig + index_t<3>{i, j, k};
        auto a = mav[ new_idx ];
        auto b = sec[{i,j,k}];
        ASSERT_EQ( a, b );
      }

  auto sec2 = mav.section( orig, {2,1,1} );

  for ( int i=0; i<2; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<1; k++ ) {
        auto new_idx = orig + index_t<3>{i, j, k};
        auto a = mav[ new_idx ];
        auto b = sec2[{i,j,k}];
        ASSERT_EQ( a, b );
      }

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the bounds iterator
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, bounds_iterator) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  strided_bounds<3> bnds{ r };  // av.bounds() is {3, 1, 2}
  ASSERT_EQ( bnds, strided_bounds<3>({3, 1, 2}) );

  // check forward iterator
  auto post_it = bnds.begin();
  auto pre_it = bnds.begin();
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        ASSERT_EQ( *post_it, index_t<3>({i, j, k}) );
        post_it++;
        ++pre_it;
      }

  ASSERT_EQ( post_it, bnds.end() );
  ASSERT_EQ( pre_it, bnds.end() );

  // check backward iterator
  for ( int i=3; i-- > 0; ) 
    for ( int j=1; j-- > 0; )
      for ( int k=2; k-- > 0; ) {
        post_it--;
        --pre_it;
        ASSERT_EQ( *post_it, index_t<3>({i, j, k}) );
      }
  
  ASSERT_EQ( post_it, bnds.begin() );
  ASSERT_EQ( pre_it, bnds.begin() );

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the bounds iterator
///////////////////////////////////////////////////////////////////////////////
TEST(strided_array_view, strided_iterator) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  strided_array_view<int, 3> view{ r };

  // check forward iterator
  auto post_it = view.begin();
  auto pre_it = view.begin();

  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        ASSERT_EQ( *post_it, r[i][j][k] );
        post_it++;
        ++pre_it;
      }

  ASSERT_EQ( post_it, view.end() );
  ASSERT_EQ( pre_it, view.end() );

  // check backward iterator
  for ( int i=3; i-- > 0; ) 
    for ( int j=1; j-- > 0; )
      for ( int k=2; k-- > 0; ) {
        post_it--;
        --pre_it;
        ASSERT_EQ( *post_it, r[i][j][k] );
      }
  
  ASSERT_EQ( post_it, view.begin() );
  ASSERT_EQ( pre_it, view.begin() );

} // TEST



///////////////////////////////////////////////////////////////////////////////
//! \brief Test the construction of array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(array_view, constructor) 
{
  auto vec = std::vector<int>(10);
  auto view = strided_array_view<int>{ vec };
  view[0] = 42;
  int v = vec[0]; // v == 42
  ASSERT_EQ( vec[0], 42 );

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  array_view<int, 3> mav{ r };  // av.bounds() is {3, 1, 2}
  array_view<int> fav{ mav };  // flatten multi-dimensional array

  ASSERT_EQ( mav.size(), 6 );
  ASSERT_EQ( mav.bounds().stride(), 2 );
  
  // check ordering
  int cnt = 0;
  for ( int i=0; i<3; i++ )
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        auto a = r[i][j][k];
        auto b = mav[{i,j,k}];
        auto c = fav[cnt++];
        auto d = mav(i, j, k);
        ASSERT_EQ( a, b );
        ASSERT_EQ( a, c );
        ASSERT_EQ( a, d );
      }
  
  // check copy constructor
  array_view<const int, 3> c_mav(mav);

  auto view_w_bounds_1 = array_view<int,2>( vec, {2,5} );
  auto view_w_bounds_2 = array_view<int,2>( vec.data(), {2,5} );

  array_view<const int,2> const_view;
  const_view = view_w_bounds_1;

  make_array_view( view_w_bounds_1 );
  make_array_view( vec );
  make_array_view( vec, 2, 5 );
  make_array_view( vec.data(), 2, 5 );

  auto view_3d = make_array_view( r );
  ASSERT_EQ( view_3d.rank(), 3 );

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the slicing array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(array_view, slice) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  array_view<int, 3> mav{ r };  // av.bounds() is {3, 1, 2}
  ASSERT_EQ( mav.bounds().stride(), 2 );

  auto slice = mav.slice( 0 );
  ASSERT_EQ( slice.size(), 2 );

  // check ordering
  for ( int j=0; j<1; j++ )
    for ( int k=0; k<2; k++ ) {
      auto a = r[0][j][k];
      auto b = slice[{j,k}];
      ASSERT_EQ( a, b );
    }

  auto orig = index_t<3>({1,0,1});
  auto sec = mav.section( orig );

  for ( int i=0; i<2; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) {
        auto new_idx = orig + index_t<3>{i, j, k};
        auto a = mav[ new_idx ];
        auto b = sec[{i,j,k}];
        ASSERT_EQ( a, b );
      }

  auto sec2 = mav.section( orig, {2,1,1} );

  for ( int i=0; i<2; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<1; k++ ) {
        auto new_idx = orig + index_t<3>{i, j, k};
        auto a = mav[ new_idx ];
        auto b = sec2[{i,j,k}];
        ASSERT_EQ( a, b );
      }

} // TEST


///////////////////////////////////////////////////////////////////////////////
//! \brief Test the slicing array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(static_array_view, bounds) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;
        
  static_bounds<3,1,2> bnds;  // av.bounds() is {3, 1, 2}
  ASSERT_EQ( bnds.as_index(), index_t<3>({ 3, 1, 2 }) );
  ASSERT_EQ( bnds.extent<0>(), 3 );
  ASSERT_EQ( bnds[0], 3 );

  ASSERT_EQ( bnds.stride(), 2 );
  
  auto slice = bnds.slice();
  ASSERT_EQ( slice.as_index(), index_t<2>({ 1, 2 }) );

  static_bounds<1> bnds_1d;
  

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the slicing array_views's.
///////////////////////////////////////////////////////////////////////////////
TEST(static_array_view, constructor) 
{

  // create a multidimensional array
  int r[3][1][2];
  for ( int i=0; i<3; i++ ) 
    for ( int j=0; j<1; j++ )
      for ( int k=0; k<2; k++ ) 
        r[i][j][k] = i + j + k;

  auto vec = std::vector<int>(10);
  std::iota( vec.begin(), vec.end(), 0 );

  
  static_array_view< int, 3,1,2 > mav{ r };

  static_array_view< int, 3,1,2 > av( vec, mav.bounds() );

  auto view = make_static_array_view<2, 5>( vec );
  ASSERT_EQ( static_cast<int>( view[ {1, 2 } ]), 7 );
  ASSERT_EQ( static_cast<int>( view(1, 2) ), 7 );

  auto view2 = make_static_array_view<10>( vec );
  ASSERT_EQ( static_cast<int>( view2[0] ), 0 );

  auto view_3d = make_static_array_view( r );


} // TEST

