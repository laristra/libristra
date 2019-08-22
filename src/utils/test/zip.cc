/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to the zip iterator.
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/zip.h"

// system includes
#include<array>
#include<cinchtest.h>
#include<iostream>
#include<list>
#include<vector>

// explicitly use some stuff
using std::cout;
using std::endl;
using std::list;
using std::vector;
using std::array;
using std::get;

using namespace ristra::utils;

//=============================================================================
//! \brief Test the "zip-like" iterator.
//=============================================================================
TEST(zip, simple) {

  vector<double> a{1.0, 2.0, 3.0, 4.0};
  list<char> b;
  b.push_back('a');
  b.push_back('b');
  b.push_back('c');
  b.push_back('d');
  array<int,4> c{4,3,2,1};
  array<int,5> c_fail{5,4,3,2,1};

  // should die
#ifndef NDEBUG
  ASSERT_DEATH( zip(a, b, c_fail), "size mismatch" );
#endif

  // now test for real
  auto d = zip( a, b, c );

  // print whats in there
  for (auto i : zip(a, b, c) ) {
    cout << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << endl;
  }

  // change a value
  //
  // for (const auto & i : d) { // works
  // for (auto & i : d) { // does not like
  // for (auto i : d) { // fine
  for (auto i : d) {
    cout << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << endl;
    get<0>(i) = 5;
  }

  // check it was actually changed
  for (auto i : d) {
    ASSERT_EQ( 5.0, get<0>(i) );
    cout << get<0>(i) << ", " << get<1>(i) << ", " << get<2>(i) << endl;
  }  

} // TEST
