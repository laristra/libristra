/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Tests related to ebedded python.
////////////////////////////////////////////////////////////////////////////////

// user includes
#include<cinchtest.h>
#include<ristra-config.h>

#ifdef RISTRA_ENABLE_PYTHON

// system includes
#include<iostream>

// Python include should go last cause it conflicts with alot of other 
// includes.
#include "ristra/utils/python_utils.h"


// explicitly use some stuff
using namespace ristra::utils;
using ristra::config::test_tolerance;

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the simple use of embedded python.
///////////////////////////////////////////////////////////////////////////////
TEST(python_utils, simple) 
{

  // setup the python interpreter
  python_initialize();

  // load the test file
  python_run_string(
    "import sys\n"
    "for path in sys.path:\n"
    "    print('path: ', path)\n"
  );

  // shut down python
  python_finalize();

} // TEST

///////////////////////////////////////////////////////////////////////////////
//! \brief Test the simple use of embedded python.
///////////////////////////////////////////////////////////////////////////////
TEST(python_utils, embedded) 
{

  // setup the python interpreter
  python_initialize();
  auto py_path = python_add_to_path(".");

  // load the test file
  auto py_module = python_import( "python_test" );

  // run a simple function and check the result
  auto py_func = python_get_attribute(py_module, "add");
  auto py_res = python_call_function( py_func, 1, 2 );
  ASSERT_EQ( 3, python_as_long(py_res) );
  ASSERT_NEAR( 3., python_as_double(py_res), test_tolerance );
  python_free(py_res);

  // try with different arguments
  py_res = python_call_function( py_func, 1., 2. );
  ASSERT_EQ( 3, python_as_long(py_res) );
  ASSERT_NEAR( 3., python_as_double(py_res), test_tolerance );
  python_free(py_res);

  // free up references.
  python_free(py_module);
  python_free(py_path);

  // shut down python
  python_finalize();

} // TEST


#endif // RISTRA_ENABLE_PYTHON
