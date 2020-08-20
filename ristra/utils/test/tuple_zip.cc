/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/tuple_zip.h"
#include "ristra/utils/tuple_visit.h"


// system includes
#include <gtest/gtest.h>
#include <iostream>
#include <string>

// using declarations
using std::cout;
using std::endl;
using std::get;
using ristra::utils::tuple_tie;
using ristra::utils::tuple_visit;
using ristra::utils::tuple_zip;

//=============================================================================
//! \brief Test the tuple_zip function.
//=============================================================================
TEST(tuple_zip, zip) {

  auto x = std::make_tuple(2, "test", 3, 8.4);
  auto y = std::make_tuple("this", 8.4, 3, 2);

  auto z = tuple_zip( x, y );
  
  tuple_visit( 
              [](auto && a) { 
                cout << get<0>(a) << " " << get<1>(a) << endl;
              },
              z );
}


//=============================================================================
//! \brief Test the tuple_tie function.
//=============================================================================
TEST(tuple_zip, tie) {

  auto x = std::make_tuple(2, 1, 3);
  auto y = std::make_tuple(1, 3, 2);

  tuple_visit( 
              [](auto && a) { 
                get<0>(a) = 1;
              },
              tuple_tie( x, y ) );


  tuple_visit( 
              [](auto && a) { 
                ASSERT_EQ( get<0>(a), 1 );
              },
              tuple_tie( x, y ) );




}
