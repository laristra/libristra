#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

#------------------------------------------------------------------------------#
# Add header files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(ristra_HEADERS
  announce.hh
  dbc.h
  detail/dbc_impl.h
  lua_access.h
  detail/lua_base.h
  detail/lua_ref.h
  detail/lua_result.h
  detail/lua_utils.h
  detail/lua_value.h
)

#------------------------------------------------------------------------------#
# Add source files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(ristra_SOURCES
  announce.cc
  detail/dbc_impl.cc
)

#------------------------------------------------------------------------------#
# Export header list to parent scope.
#------------------------------------------------------------------------------#

set(ristra_HEADERS
  ${ristra_HEADERS}
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Export source list to parent scope.
#------------------------------------------------------------------------------#

set(ristra_SOURCES
  ${ristra_SOURCES}
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Unit tests.
#------------------------------------------------------------------------------#

cinch_add_unit(ristra-test
  SOURCES
    test/test-announce.cc
    test/lua_utils.cc
  LIBRARIES ristra ${RISTRA_LIBRARIES}
  INPUTS
    test/lua_test.lua
)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
