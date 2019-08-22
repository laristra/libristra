#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_library( ${PROJECT_NAME}_assertions
  OBJECT
  dbc.h
  detail/dbc_impl.h
  errors.h
  exceptions.h
  here.h
  detail/dbc_impl.cc
)

#cinch_add_unit( dbc_notify
#  SOURCES
#    test/dbc_test_notify.cc
#  LIBRARIES Ristra
#)
#
#cinch_add_unit( dbc_no_assert
#  SOURCES
#    test/dbc_test_no_assert.cc
#  LIBRARIES Ristra
#)
#
#
#cinch_add_unit( dbc
#  SOURCES
#    test/dbc_test.cc
#    test/dbc_test_no_assert.cc
#  LIBRARIES Ristra
#)
