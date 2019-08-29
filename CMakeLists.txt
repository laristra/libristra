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

cmake_minimum_required(VERSION 2.8)

#------------------------------------------------------------------------------#
# Set the project name
#------------------------------------------------------------------------------#

project(Ristra)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
include(cmake/unit.cmake)

#------------------------------------------------------------------------------#
# If a C++17 compiler is available, then set the appropriate flags
#------------------------------------------------------------------------------#

# We need C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

#------------------------------------------------------------------------------#
# Enable exceptions
#------------------------------------------------------------------------------#

OPTION (RISTRA_ENABLE_EXCEPTIONS "Enable C++ exceptions (really?)"  ON)

#------------------------------------------------------------------------------#
# Some precision setup
#------------------------------------------------------------------------------#

# double or single precision
OPTION (RISTRA_DOUBLE_PRECISION "Use double precision reals"  ON)

if( RISTRA_DOUBLE_PRECISION )
  message(STATUS "Note: Double precision build activated.")
  SET (RISTRA_TEST_TOLERANCE 1.0e-14 CACHE STRING "The testing tolerance" )
else()
  message(STATUS "Note: Single precision build activated.")
  SET (RISTRA_TEST_TOLERANCE 1.0e-6 CACHE STRING "The testing tolerance" )
endif()

#------------------------------------------------------------------------------#
# Support for embedded interpreters
#------------------------------------------------------------------------------#

find_package(PythonLibs QUIET)

option(RISTRA_ENABLE_PYTHON "Enable Python Support" ${PYTHONLIBS_FOUND})

if(RISTRA_ENABLE_PYTHON AND NOT PYTHONLIBS_FOUND)
  message(FATAL_ERROR "Python requested, but not found")
endif()

if (RISTRA_ENABLE_PYTHON)
   message (STATUS "Found PythonLibs: ${PYTHON_INCLUDE_DIRS}")
   include_directories( ${PYTHON_INCLUDE_DIRS} )
   target_link_libraries( ${PROJECT_NAME} PUBLIC ${PYTHON_LIBRARIES} )
endif ()

#------------------------------------------------------------------------------#
# Lua
#------------------------------------------------------------------------------#

# lua_rawlen requires Lua version 5.2 at least
find_package(Lua 5.2 QUIET)

option(RISTRA_ENABLE_LUA "Enable Lua Support" ${LUA_FOUND})

if(RISTRA_ENABLE_LUA AND NOT LUA_FOUND)
  message(FATAL_ERROR "Lua requested, but not found")
endif()

if(RISTRA_ENABLE_LUA)
   message (STATUS "Found Lua: ${LUA_INCLUDE_DIR}")
   include_directories(${LUA_INCLUDE_DIR})
   target_link_libraries( ${PROJECT_NAME} PUBLIC ${LUA_LIBRARIES} ${CMAKE_DL_LIBS} )
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

#------------------------------------------------------------------------------#
# Google test
#------------------------------------------------------------------------------#
option(RISTRA_ENABLE_UNIT_TESTS "Enable unit testing" OFF)

set( GTEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/gtest )
file(GLOB _gtest_contents ${GTEST_DIR}/*)

if (RISTRA_ENABLE_UNIT_TESTS)
  enable_testing()
  if (_gtest_contents)
    add_subdirectory( ${GTEST_DIR} )
  else()
    find_package(GTest REQUIRED)
  endif()
endif()


#------------------------------------------------------------------------------#
# configure library
#------------------------------------------------------------------------------#

add_library( ${PROJECT_NAME} )
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(ristra)


#------------------------------------------------------------------------------#
# Extract all project options so they can be exported to the ProjectConfig.cmake
# file.
#------------------------------------------------------------------------------#

get_cmake_property(_variableNames VARIABLES)
string (REGEX MATCHALL "(^|;)RISTRA_[A-Za-z0-9_]*" _matchedVars "${_variableNames}")
foreach (_variableName ${_matchedVars})
  set( RISTRA_CONFIG_CODE
    "${RISTRA_CONFIG_CODE}
set(${_variableName} \"${${_variableName}}\")"
  )
endforeach()

#------------------------------------------------------------------------------#
# Prepare variables for ProjectConfig file.
#------------------------------------------------------------------------------#

get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  PROPERTY INCLUDE_DIRECTORIES)

foreach(dir ${dirs})
  if(NOT ${dir} MATCHES ${CMAKE_CURRENT_SOURCE_DIR})
    list(APPEND RISTRA_EXTERNAL_INCLUDE_DIRS ${dir})
  endif()
endforeach()

#------------------------------------------------------------------------------#
# Export targets and package.
#------------------------------------------------------------------------------#

export(
  TARGETS ${PROJECT_NAME}
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraTargets.cmake
)

export(PACKAGE ${PROJECT_NAME})

install( TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}Targets
       	DESTINATION lib PUBLIC_HEADER DESTINATION include) 

#------------------------------------------------------------------------------#
# configure .cmake file (for other projects)
#------------------------------------------------------------------------------#

configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake @ONLY)

install(
  FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/${PROJECT_NAME}Config.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/${PROJECT_NAME}
)

install(
  EXPORT ${PROJECT_NAME}Targets
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/${PROJECT_NAME}
  COMPONENT dev
)
