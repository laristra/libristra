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
   list( APPEND RISTRA_LIBRARIES ${PYTHON_LIBRARIES} )
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
   list(APPEND RISTRA_LIBRARIES ${LUA_LIBRARIES})
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
# Caliper
#------------------------------------------------------------------------------#

find_package(Caliper QUIET)

option(RISTRA_ENABLE_CALIPER "Enable Caliper Support" ${Caliper_FOUND})

if(RISTRA_ENABLE_CALIPER AND NOT Caliper_FOUND)
  message(FATAL_ERROR "Caliper requested, but not found")
endif()

if(RISTRA_ENABLE_CALIPER)
  message(STATUS "Found Caliper: ${Caliper_INCLUDE_DIRS}")
  include_directories(${Caliper_INCLUDE_DIRS})
  list( APPEND RISTRA_LIBRARIES ${Caliper_LIBRARIES} )
endif()

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
# Legion / MPI
#------------------------------------------------------------------------------#

find_package(MPI)

option(RISTRA_ENABLE_MPI "Enable MPI Support" ${MPI_FOUND})

if(RISTRA_ENABLE_MPI AND NOT MPI_FOUND)
  message(FATAL_ERROR "MPI requested, but not found")
endif()

if(RISTRA_ENABLE_MPI)
  include_directories(${MPI_C_INCLUDE_PATH})
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
install(FILES ${CMAKE_BINARY_DIR}/ristra.h DESTINATION include)

configure_file(${PROJECT_SOURCE_DIR}/config/ristra-config.h.in
  ${CMAKE_BINARY_DIR}/ristra-config.h @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/ristra-config.h DESTINATION include)

include_directories(${CMAKE_BINARY_DIR})

#------------------------------------------------------------------------------#
# Add library targets
#------------------------------------------------------------------------------#

cinch_add_library_target(Ristra ristra)

#------------------------------------------------------------------------------#
# configure .cmake file (for other projects)
#------------------------------------------------------------------------------#

export(
  TARGETS Ristra
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraTargets.cmake
)

export(PACKAGE Ristra)

set(RISTRA_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRA_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(RISTRA_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/Ristra)

configure_file(${PROJECT_SOURCE_DIR}/config/RistraConfig.cmake.in
  ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraConfig.cmake @ONLY)

install(
  FILES ${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraConfig.cmake
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/Ristra
)

install(
  EXPORT RistraTargets
  DESTINATION ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/Ristra
  COMPONENT dev
)

#------------------------------------------------------------------------------#
# Add distclean target
#------------------------------------------------------------------------------#

add_custom_target(distclean rm -rf ${CMAKE_BINARY_DIR}/*)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
# sublime: none needed--NYUK NYUK NYUK!
#~---------------------------------------------------------------------------~-#
