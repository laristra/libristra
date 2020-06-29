#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

if (RISTRA_ENABLE_LUA)
  ristra_add_unit( ristra_lua_utils
    SOURCES test/lua_utils.cc
    INPUTS test/lua_test.lua test/mock_box_2d.lua
    LIBRARIES Ristra )
endif()

cinch_add_unit( ristra_lua_utils
  SOURCES test/lua_utils.cc
  INPUTS test/lua_test.lua test/mock_box_2d.lua
  LIBRARIES Ristra )

if(RISTRA_ENABLE_PYTHON)
  cinch_add_unit( ristra_python_utils 
    SOURCES test/python_utils.cc 
    INPUTS test/python_test.py
    LIBRARIES Python3::Python )
endif()
