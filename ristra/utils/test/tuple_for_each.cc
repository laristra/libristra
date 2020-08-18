/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/tuple_for_each.h"


// system includes
#include <gtest/gtest.h>
#include <iostream>
#include <string>

// using declarations
using std::cout;
using std::endl;
using std::get;
using ristra::utils::tuple_for_each;

//=============================================================================
//! \brief Test the tuple_zip function.
//=============================================================================
TEST(tuple_for_each, simple) {

  auto x = std::make_tuple(2, "test", 3, 8.4);

  tuple_for_each( x, 
                  [](auto & tup) { 
                    cout << tup << endl; 
                  } );
}

