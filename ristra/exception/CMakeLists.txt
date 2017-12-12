#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(exception_HEADERS
  dbc/dbc.h
  dbc/dbc_impl.h
  errors.h
  exceptions.h
  here.h
  
  PARENT_SCOPE # THIS NEEDS TO BE HERE
)

set(exception_SOURCES
  dbc/dbc_impl.cc
  PARENT_SCOPE
)

cinch_add_unit( dbc_notify
  SOURCES
    dbc/test/dbc_test_notify.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)


cinch_add_unit( dbc
  SOURCES
    dbc/test/dbc_test.cc
    dbc/test/dbc_test_no_assert.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
