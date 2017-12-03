#~----------------------------------------------------------------------------~#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(math_HEADERS
  array.h
  constants.h
  detail/general_impl.h
  general.h
  matrix.h
  multi_array.h
  tuple.h
  vector.h
  PARENT_SCOPE
)

set(math_SOURCES
  PARENT_SCOPE
)

cinch_add_unit(test_tuple SOURCES test/tuple.cc)
cinch_add_unit(test_vector SOURCES test/vector.cc)
cinch_add_unit(test_matrix SOURCES test/matrix.cc)

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
