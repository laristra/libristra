#~----------------------------------------------------------------------------~#
#
# TO DO: awesome Ristra ascii art here
#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

#------------------------------------------------------------------------------#
# Set the minimum Cinch version
#------------------------------------------------------------------------------#

cinch_minimum_required(1.0)

#------------------------------------------------------------------------------#
# Set the project name
#------------------------------------------------------------------------------#

project(ristra CXX)

#------------------------------------------------------------------------------#
# Set header suffix regular expression
#------------------------------------------------------------------------------#

set(CINCH_HEADER_SUFFIXES "\\.h")

#------------------------------------------------------------------------------#
# If a C++14 compiler is available, then set the appropriate flags
#------------------------------------------------------------------------------#

include(cxx14)

check_for_cxx14_compiler(CXX14_COMPILER)

if(CXX14_COMPILER)
    enable_cxx14()
else()
    message(FATAL_ERROR "C++14 compatible compiler not found")
endif()

#------------------------------------------------------------------------------#
# Boost
#
# Note that this find package only sets the header information. To find
# library dependencies, add COMPONENTS and specify the ones that you need.
#------------------------------------------------------------------------------#

# TO DO: how important is this version of Boost? Can change to >= 1.58?
find_package(Boost 1.58.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

#------------------------------------------------------------------------------#
# Add options for design by contract
#------------------------------------------------------------------------------#

set(RISTRA_DBC_ACTIONS throw notify nothing)

if(NOT RISTRA_DBC_ACTION)
  list(GET RISTRA_DBC_ACTIONS 0 RISTRA_DBC_ACTION)
endif()

set(RISTRA_DBC_ACTION "${RISTRA_DBC_ACTION}" CACHE STRING
  "Select the design by contract action")
set_property(CACHE RISTRA_DBC_ACTION PROPERTY STRINGS ${RISTRA_DBC_ACTIONS})

set(FLECSI_DBC_REQUIRE ON CACHE BOOL
  "Enable DBC Pre/Post Condition Assertions")

if(RISTRA_DBC_ACTION STREQUAL "throw")
  add_definitions(-DRISTRA_DBC_THROW)
elseif(RISTRA_DBC_ACTION STREQUAL "notify")
  add_definitions(-DRISTRA_DBC_NOTIFY)
endif()

if(RISTRA_DBC_REQUIRE)
  add_definitions(-DRISTRA_REQUIRE_ON)
endif()

#------------------------------------------------------------------------------#
# Load the cinch extras
#------------------------------------------------------------------------------#

cinch_load_extras()

#------------------------------------------------------------------------------#
# configure header
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/config/ristra.h.in
  ${CMAKE_BINARY_DIR}/ristra.h @ONLY)
include_directories(${CMAKE_BINARY_DIR})
install(FILES ${CMAKE_BINARY_DIR}/ristra.h DESTINATION include)

#------------------------------------------------------------------------------#
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(ristra ristra)

#------------------------------------------------------------------------------#
# Add distclean target
#------------------------------------------------------------------------------#

add_custom_target(distclean rm -rf ${CMAKE_BINARY_DIR}/*)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
# sublime: none needed--NYUK NYUK NYUK!
#~---------------------------------------------------------------------------~-#
