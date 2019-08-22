#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_library( ${PROJECT_NAME}_embedded
  OBJECT
  embed_lua.h
  embed_python.h
)


add_unit( ristra_lua_utils
  SOURCES test/lua_utils.cc
  INPUTS test/lua_test.lua test/mock_box_2d.lua
  LIBRARIES Ristra )

add_unit( ristra_python_utils 
  SOURCES test/python_utils.cc 
  INPUTS test/python_test.py
  LIBRARIES ${PYTHON_LIBRARIES} )
