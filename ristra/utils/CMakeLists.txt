#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(utils_HEADERS
  algorithm.h
  array_ref.h
  array_view.h
  const_string.h
  detail/array_view_impl.h
  detail/template_helpers_impl.h
  detail/tuple_for_each_impl.h
  detail/tuple_visit_impl.h
  detail/tuple_zip_impl.h
  detail/type_traits_impl.h
  detail/zip_impl.h
  dimensioned_array.h
  filter_iterator.h
  fixed_vector.h
  functional.h
  static_for.h
  string_utils.h
  static_warning.h
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

cinch_add_unit( ristra_array_view SOURCES test/array_view.cc )

cinch_add_unit( ristra_caliper
  SOURCES test/caliper.cc
  LIBRARIES ${Caliper_LIBRARIES} )

cinch_add_unit( ristra_fixed_vector SOURCES test/fixed_vector.cc )

cinch_add_unit( ristra_static_for SOURCES test/static_for.cc )
cinch_add_unit( ristra_tasks SOURCES test/tasks.cc )
cinch_add_unit( ristra_tuple_for_each SOURCES test/tuple_for_each.cc )
cinch_add_unit( ristra_tuple_visit SOURCES test/tuple_visit.cc )
cinch_add_unit( ristra_tuple_zip SOURCES test/tuple_zip.cc )
cinch_add_unit( ristra_type_traits_helpers SOURCES test/type_traits_helpers.cc )
cinch_add_unit( ristra_zip SOURCES test/zip.cc )

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
