#~----------------------------------------------------------------------------~#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_library( ${PROJECT_NAME}_io
  OBJECT
  catalyst/adaptor.h
  vtk.h
  write_binary.h
  vtk.cc
)
