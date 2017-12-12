#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(utils_HEADERS
  algorithm.h
  array_ref.h
  array_view.h
  const_string.h
  dbc.h
  detail/array_view_impl.h
  detail/dbc_impl.h
  detail/template_helpers_impl.h
  detail/tuple_for_each_impl.h
  detail/tuple_visit_impl.h
  detail/tuple_zip_impl.h
  detail/type_traits_impl.h
  detail/zip_impl.h
  dimensioned_array.h
  errors.h
  exceptions.h
  filter_iterator.h
  fixed_vector.h
  functional.h
  here.h
  static_for.h
  string_utils.h
  tasks.h
  template_helpers.h
  time_utils.h
  trivial_string.h
  tuple_for_each.h
  tuple_to_array.h
  tuple_visit.h
  tuple_zip.h
  type_traits.h
  zip.h
  
  PARENT_SCOPE # THIS NEEDS TO BE HERE
)

set(utils_SOURCES
  detail/dbc_impl.cc
  PARENT_SCOPE
)

cinch_add_unit( array_view SOURCES test/array_view.cc )

cinch_add_unit( caliper
  SOURCES test/caliper.cc
  LIBRARIES ${Caliper_LIBRARIES} )

cinch_add_unit( fixed_vector SOURCES test/fixed_vector.cc )

cinch_add_unit( static_for SOURCES test/static_for.cc )
cinch_add_unit( tasks SOURCES test/tasks.cc )
cinch_add_unit( tuple_for_each SOURCES test/tuple_for_each.cc )
cinch_add_unit( tuple_visit SOURCES test/tuple_visit.cc )
cinch_add_unit( tuple_zip SOURCES test/tuple_zip.cc )
cinch_add_unit( type_traits_helpers SOURCES test/type_traits_helpers.cc )
cinch_add_unit( zip SOURCES test/zip.cc )

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

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
