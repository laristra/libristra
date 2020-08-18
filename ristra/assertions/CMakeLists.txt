#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

target_sources( Ristra PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/dbc_impl.cc )

ristra_add_unit( dbc_notify
  SOURCES
    test/dbc_test_notify.cc
  LIBRARIES Ristra
)

ristra_add_unit( dbc_no_assert
  SOURCES
    test/dbc_test_no_assert.cc
  LIBRARIES Ristra
)


ristra_add_unit( dbc
  SOURCES
    test/dbc_test.cc
    test/dbc_test_no_assert.cc
  LIBRARIES Ristra
)
