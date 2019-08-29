#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

target_sources( ${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/announce.cc )

add_unit(ristra_initialization
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
