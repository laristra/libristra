#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

#------------------------------------------------------------------------------#
# Add header files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(ristra_HEADERS
  announce.h
  dbc.h
  detail/dbc_impl.h
  detail/default_input_traits.h
  detail/inputs_impl.h
  detail/lua_base.h
  detail/lua_ref.h
  detail/lua_result.h
  detail/lua_utils.h
  detail/lua_value.h
  detail/math_utils_impl.h
  detail/template_helpers.h
  detail/template_helpers_impl.h
  detail/type_traits_impl.h
  detail/type_utils.h
  errors.h
  flecsale-array.h
  flecsale-vector.h
  here.h
  init_value.h
  input_engine.h
  input_source.h
  lua_access.h
  math_utils.h
  static_warning.h
  type_traits.h
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Add source files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(ristra_SOURCES
  announce.cc
  detail/dbc_impl.cc
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Unit tests.
#------------------------------------------------------------------------------#

cinch_add_unit(ristra-test
  SOURCES
    #announce.cc
    test/test-announce.cc
    test/lua_utils.cc
    test/init_value.cc
    test/input_source.cc
    test/input_engine.cc
    test/test_input_hard_coded_problems.cc
    test/type_traits.cc
    test/flecsale-vector.cc
  LIBRARIES Ristra ${RISTRA_LIBRARIES}
  INPUTS
    test/lua_test.lua
    test/mock_box_2d.lua
)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
