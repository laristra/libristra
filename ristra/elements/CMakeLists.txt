#~----------------------------------------------------------------------------~#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

set(elements_HEADERS
  elements.h
  utilities.h
  PARENT_SCOPE
)

set(elements_SOURCES
  elements.cc
  PARENT_SCOPE
)

cinch_add_unit(ristra_elements SOURCES test/examples.cc LIBRARIES Ristra)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
