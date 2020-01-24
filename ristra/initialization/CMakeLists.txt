#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

#------------------------------------------------------------------------------#
# Add header files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(initialization_HEADERS
  announce.h
  arguments.h
  detail/inputs_impl.h
  input.h
  init_value.h
  input_engine.h
  input_source.h
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Add source files. Note that these will be "exported" to the parent
# scope below.
#------------------------------------------------------------------------------#

set(initialization_SOURCES
  announce.cc
  PARENT_SCOPE
)

#------------------------------------------------------------------------------#
# Unit tests.
#------------------------------------------------------------------------------#

cinch_add_unit(ristra_initialization
  SOURCES
    test/test-announce.cc
    test/init_value.cc
    test/input_source.cc
    test/input_engine.cc
    test/test_input_hard_coded_problems.cc
  LIBRARIES Ristra
  INPUTS
    test/mock_box_2d.lua
)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
