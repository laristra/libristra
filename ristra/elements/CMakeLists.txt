#~----------------------------------------------------------------------------~#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

target_sources( ${PROJECT_NAME} PRIVATE  ${CMAKE_CURRENT_SOURCE_DIR}/elements.cc )

ristra_add_unit(ristra_elements SOURCES test/examples.cc LIBRARIES Ristra)
