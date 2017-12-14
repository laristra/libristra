#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(assertions_HEADERS
  dbc.h
  detail/dbc_impl.h
  errors.h
  exceptions.h
  here.h
  
  PARENT_SCOPE # THIS NEEDS TO BE HERE
)

set(assertions_SOURCES
  detail/dbc_impl.cc
  PARENT_SCOPE
)

cinch_add_unit( dbc_notify
  SOURCES
    test/dbc_test_notify.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)


cinch_add_unit( dbc
  SOURCES
    test/dbc_test.cc
    test/dbc_test_no_assert.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)
