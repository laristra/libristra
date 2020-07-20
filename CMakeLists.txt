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

cmake_minimum_required(VERSION 3.12)

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

if(NOT TARGET Python3::Python)
  find_package(Python3 COMPONENTS Development)
endif()

option(RISTRA_ENABLE_PYTHON "Enable Python Support" Python3_FOUND)

if(RISTRA_ENABLE_PYTHON AND NOT Python3_FOUND)
  message(FATAL_ERROR "Python requested, but not found")
endif()

if (RISTRA_ENABLE_PYTHON)
  message (STATUS "Found Python3 Development Libraries: ${Python3_INCLUDE_DIRS}")
  # We should remove these general commands to avoid polluting other build systems
  include_directories( ${Python3_INCLUDE_DIRS} )
  list( APPEND RISTRA_LIBRARIES Python3::Python )
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
# Catalyst
#------------------------------------------------------------------------------#

option(RISTRA_ENABLE_CATALYST "Link the sim with Catalyst for in situ" OFF)

if (RISTRA_ENABLE_CATALYST)
  find_package(ParaView REQUIRED COMPONENTS vtkPVPythonCatalyst)

  message(STATUS "Found Paraview: ${ParaView_DIR}")
  message(STATUS "IO with Paraview Catalyst enabled" )

  include("${PARAVIEW_USE_FILE}")

  if (NOT PARAVIEW_USE_MPI)
    message(SEND_ERROR "ParaView must be built with MPI enabled")
  endif()

  list( APPEND RISTRA_LIBRARIES vtkPVPythonCatalyst vtkParallelMPI )
endif()

#------------------------------------------------------------------------------#
# Google test
#------------------------------------------------------------------------------#
option(ENABLE_UNIT_TESTS "Enable unit testing" OFF)

if (ENABLE_UNIT_TESTS)
  enable_testing()
  find_package(GTest REQUIRED)
endif()

#------------------------------------------------------------------------------#
# Legion / MPI
#------------------------------------------------------------------------------#

find_package(MPI COMPONENTS C CXX REQUIRED)

option(RISTRA_ENABLE_MPI "Enable MPI Support" ${MPI_FOUND})

if(RISTRA_ENABLE_MPI AND NOT MPI_FOUND)
  message(FATAL_ERROR "MPI requested, but not found")
endif()

if(RISTRA_ENABLE_MPI)
  list( APPEND RISTRA_LIBRARIES  MPI::MPI_CXX MPI::MPI_C)
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

export(
  TARGETS Ristra
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraTargets.cmake
)
export(PACKAGE Ristra)