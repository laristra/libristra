#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_unit( ristra_array_view SOURCES test/array_view.cc LIBRARIES Ristra )

add_unit( ristra_caliper
  SOURCES test/caliper.cc
  LIBRARIES Ristra ${Caliper_LIBRARIES} )

add_unit( ristra_fixed_vector SOURCES test/fixed_vector.cc LIBRARIES Ristra)

add_unit( ristra_static_for SOURCES test/static_for.cc LIBRARIES Ristra)
add_unit( ristra_tasks SOURCES test/tasks.cc LIBRARIES Ristra)
add_unit( ristra_tuple_for_each SOURCES test/tuple_for_each.cc LIBRARIES Ristra)
add_unit( ristra_tuple_visit SOURCES test/tuple_visit.cc LIBRARIES Ristra)
add_unit( ristra_tuple_zip SOURCES test/tuple_zip.cc LIBRARIES Ristra)
add_unit( ristra_type_traits_helpers SOURCES test/type_traits_helpers.cc LIBRARIES Ristra)
add_unit( ristra_zip SOURCES test/zip.cc LIBRARIES Ristra)
