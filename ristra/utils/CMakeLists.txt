#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(utils_HEADERS
  algorithm.h
  array_ref.h
  array_view.h
  const_string.h
  dbc.h              detail/dbc_impl.h
  dimensioned_array.h
  exceptions.h
  errors.h
  filter_iterator.h
  fixed_vector.h
  functional.h
  lua_utils.h
  python_utils.h
  string_utils.h
  static_for.h
  tasks.h
  template_helpers.h detail/template_helpers_impl.h
  time_utils.h
  tuple_for_each.h   detail/tuple_for_each_impl.h
  tuple_visit.h      detail/tuple_visit_impl.h
  tuple_zip.h        detail/tuple_zip_impl.h
  type_traits.h      detail/type_traits_impl.h
  zip.h              detail/zip_impl.h
  
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

cinch_add_unit( lua_utils
  SOURCES test/lua_utils.cc
  INPUTS test/lua_test.lua
  LIBRARIES ${LUA_LIBRARIES} )

cinch_add_unit( python_utils 
  SOURCES test/python_utils.cc 
  INPUTS test/python_test.py
  LIBRARIES ${PYTHON_LIBRARIES} )

cinch_add_unit( static_for SOURCES test/static_for.cc )
cinch_add_unit( tasks SOURCES test/tasks.cc )
cinch_add_unit( tuple_for_each SOURCES test/tuple_for_each.cc )
cinch_add_unit( tuple_visit SOURCES test/tuple_visit.cc )
cinch_add_unit( tuple_zip SOURCES test/tuple_zip.cc )
cinch_add_unit( type_traits_helpers SOURCES test/type_traits_helpers.cc )
cinch_add_unit( zip SOURCES test/zip.cc )

cinch_add_unit( dbc
  SOURCES
    test/dbc_test.cc
    test/dbc_test_no_assert.cc
    test/dbc_test_notify.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
