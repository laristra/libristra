#~----------------------------------------------------------------------------~#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_library( ${PROJECT_NAME}_math
  OBJECT
  array.h
  constants.h
  detail/general_impl.h
  general.h
  matrix.h
  multi_array.h
  tuple.h
  vector.h
)

add_unit(ristra_tuple SOURCES test/tuple.cc)
add_unit(ristra_vector SOURCES test/vector.cc)
add_unit(ristra_matrix SOURCES test/matrix.cc)
