#~----------------------------------------------------------------------------~#
# Copyright (c) 2017 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(embedded_HEADERS
  detail/lua_base.h
  detail/lua_ref.h
  detail/lua_result.h
  detail/lua_utils.h
  detail/lua_value.h
  embed_lua.h
  embed_python.h
  
  PARENT_SCOPE # THIS NEEDS TO BE HERE
)

cinch_add_unit( lua_utils
  SOURCES test/lua_utils.cc
  INPUTS test/lua_test.lua test/mock_box_2d.lua
  LIBRARIES Ristra )

cinch_add_unit( python_utils 
  SOURCES test/python_utils.cc 
  INPUTS test/python_test.py
  LIBRARIES ${PYTHON_LIBRARIES} )

#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
