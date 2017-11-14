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

project(Ristra)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

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
# Enable exceptions
#------------------------------------------------------------------------------#

OPTION (ENABLE_EXCEPTIONS "Enable C++ exceptions (really?)"  ON)
if(ENABLE_EXCEPTIONS)
  add_definitions( -DENABLE_EXCEPTIONS)
endif()

#------------------------------------------------------------------------------#
# Some precision setup
#------------------------------------------------------------------------------#

# double or single precision
OPTION (DOUBLE_PRECISION "Use double precision reals"  ON)

if( DOUBLE_PRECISION )
  message(STATUS "Note: Double precision build activated.")
  add_definitions( -DDOUBLE_PRECISION )
  SET (TEST_TOLERANCE 1.0e-14 CACHE STRING "The testing tolerance" )
else()
  message(STATUS "Note: Single precision build activated.")
  SET (TEST_TOLERANCE 1.0e-6 CACHE STRING "The testing tolerance" )
endif()

add_definitions( -DTEST_TOLERANCE=${TEST_TOLERANCE} )

#------------------------------------------------------------------------------#
# Support for embedded interpreters
#------------------------------------------------------------------------------#

find_package(PythonLibs QUIET)

option(ENABLE_PYTHON "Enable Python Support" ${PYTHONLIBS_FOUND})

if(ENABLE_PYTHON AND NOT PYTHONLIBS_FOUND)
  message(FATAL_ERROR "Python requested, but not found")
endif()

if (ENABLE_PYTHON)
   message (STATUS "Found PythonLibs: ${PYTHON_INCLUDE_DIRS}")
   include_directories( ${PYTHON_INCLUDE_DIRS} )
   list( APPEND RISTRA_LIBRARIES ${PYTHON_LIBRARIES} )
   add_definitions( -DHAVE_PYTHON )
endif ()

# find lua for embedding
# Note: Not sure about the version: I'm OK with Lua 3.3
find_package(Lua 5 QUIET)

option(ENABLE_LUA "Enable Lua Support" ${LUA_FOUND})

if(ENABLE_LUA AND NOT LUA_FOUND)
  message(FATAL_ERROR "Lua requested, but not found")
endif()

if (ENABLE_LUA)
   message (STATUS "Found Lua: ${LUA_INCLUDE_DIR}")
   include_directories( ${LUA_INCLUDE_DIR} )
   list( APPEND RISTRA_LIBRARIES ${LUA_LIBRARIES} )
   add_definitions( -DHAVE_LUA )
endif ()

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

set(RISTRA_DBC_REQUIRE ON CACHE BOOL
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

cinch_add_library_target(Ristra ristra)

#------------------------------------------------------------------------------#
# configure .cmake file (for other projects)
#------------------------------------------------------------------------------#

set(CONF_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
set(CONF_LIB_DIRS "${CMAKE_INSTALL_PREFIX}/lib")
set(CONF_LIB_NAME "${CONF_LIB_DIRS}/libristra${CMAKE_SHARED_LIBRARY_SUFFIX}")
message(STATUS "CMAKE_SHARED_LIBRARY_SUFFIX = " ${CMAKE_SHARED_LIBRARY_SUFFIX})

configure_file(${PROJECT_SOURCE_DIR}/config/RistraConfig.cmake.in
  "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraConfig.cmake" @ONLY)

install(FILES "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraConfig.cmake"
  DESTINATION share/cmake)

#------------------------------------------------------------------------------#
# Add distclean target
#------------------------------------------------------------------------------#

add_custom_target(distclean rm -rf ${CMAKE_BINARY_DIR}/*)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
# sublime: none needed--NYUK NYUK NYUK!
#~---------------------------------------------------------------------------~-#
