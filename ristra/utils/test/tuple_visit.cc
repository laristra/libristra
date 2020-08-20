/*~--------------------------------------------------------------------------~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~--------------------------------------------------------------------------~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
////////////////////////////////////////////////////////////////////////////////

// user includes
#include "ristra/utils/tuple_visit.h"


// system includes
#include <gtest/gtest.h>
#include <iostream>
#include <string>

// using declarations
using std::cout;
using std::endl;
using ristra::utils::tuple_visit;

//=============================================================================
//! \brief Test the tuple_visit function.
//=============================================================================
TEST(tuple_visit, simple) {

  struct NonPrintable { };

  auto x = std::make_tuple(2, "test", 3, 8.4);
  auto y = std::make_tuple("this", 8.4, 3, 2);

  tuple_visit( 
              [](const auto & a, const auto & b) { 
                cout << a << " " << b << endl;
              },
              x, y );


}
