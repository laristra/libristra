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

cmake_minimum_required(VERSION 3.5.2)

#------------------------------------------------------------------------------#
# Setup the project
#------------------------------------------------------------------------------#

project(Ristra VERSION 2.0.0)

include(cmake/ristra_helpers.cmake)

add_library( Ristra )

# We need C++ 17
set_property(TARGET Ristra PROPERTY CXX_STANDARD 17)
set_property(TARGET Ristra PROPERTY CXX_STANDARD 17)
set_property(TARGET Ristra PROPERTY CXX_STANDARD_REQUIRED on)
set_property(TARGET Ristra PROPERTY CXX_EXTENSIONS off)

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
   target_include_directories(Ristra  PUBLIC ${PYTHON_INCLUDE_DIRS} )
   target_link_libraries( Ristra PUBLIC ${PYTHON_LIBRARIES} )
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
   target_include_directories( Ristra PUBLIC ${LUA_INCLUDE_DIR} )
   target_link_libraries( Ristra PUBLIC ${LUA_LIBRARIES} ${CMAKE_DL_LIBS} )
endif ()

#------------------------------------------------------------------------------#
# Boost
#
# Note that this find package only sets the header information. To find
# library dependencies, add COMPONENTS and specify the ones that you need.
#------------------------------------------------------------------------------#

find_package(Boost 1.58.0 REQUIRED)
target_link_libraries(Ristra PUBLIC Boost::boost)

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

add_subdirectory(cmake)

target_include_directories( Ristra PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
	$<INSTALL_INTERFACE:include> )

add_subdirectory(ristra)


#------------------------------------------------------------------------------#
# Export targets and package.
#------------------------------------------------------------------------------#

install( TARGETS Ristra
 	EXPORT ${PROJECT_NAME}Targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include) 

install( EXPORT ${PROJECT_NAME}Targets
	FILE ${PROJECT_NAME}Targets.cmake
	NAMESPACE Ristra::
	DESTINATION lib/cmake/${PROJECT_NAME}
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file("${PROJECT_NAME}ConfigVersion.cmake"
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY SameMajorVersion
)

configure_file(${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.cmake.in
  ${PROJECT_NAME}Config.cmake @ONLY)

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
 	"${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}ConfigVersion.cmake"
	DESTINATION lib/cmake/${PROJECT_NAME}
)

