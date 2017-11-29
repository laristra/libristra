#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(utils_HEADERS
  array_ref.h
  dbc.h
  detail/dbc_impl.h
  detail/template_helpers_impl.h
  detail/tuple_visit_impl.h
  detail/type_traits_impl.h
  dimensioned_array.h
  errors.h
  exceptions.h
  fixed_vector.h
  string_utils.h
  template_helpers.h
  tuple_visit.h
  type_traits.h
  PARENT_SCOPE
)

set(utils_SOURCES
  detail/dbc_impl.cc
  PARENT_SCOPE
)

cinch_add_unit(ristra-utils-test
  SOURCES
    test/dbc_test.cc
    test/dbc_test_no_assert.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)

cinch_add_unit(ristra-dbc-notify-test
  SOURCES
    test/dbc_test_notify.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
