#~----------------------------------------------------------------------------~#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

add_library( ${PROJECT_NAME}_elements
  OBJECT
  elements.h
  utilities.h
  elements.cc
)
#cinch_add_unit(ristra_elements SOURCES test/examples.cc LIBRARIES Ristra)
