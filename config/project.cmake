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

cinch_minimum_required(VERSION v1.0)

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

if(NOT TARGET Python::Python)
  find_package(Python COMPONENTS Development)
endif()

option(RISTRA_ENABLE_PYTHON "Enable Python Support" Python_FOUND)

if(RISTRA_ENABLE_PYTHON AND NOT Python_FOUND)
  message(FATAL_ERROR "Python requested, but not found")
endif()

if (RISTRA_ENABLE_PYTHON)
   message (STATUS "Found PythonLibs: ${Python_INCLUDE_DIRS}")
   include_directories( ${Python_INCLUDE_DIRS} )
   list( APPEND RISTRA_LIBRARIES Python::Python )
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
   list(APPEND RISTRA_LIBRARIES ${LUA_LIBRARIES} ${CMAKE_DL_LIBS})
endif ()

#------------------------------------------------------------------------------#
# Boost
#
# Note that this find package only sets the header information. To find
# library dependencies, add COMPONENTS and specify the ones that you need.
#------------------------------------------------------------------------------#

# TO DO: how important is this version of Boost? Can change to >= 1.58?
find_package(Boost 1.59.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
list(APPEND RISTRA_LIBRARIES Boost::boost)

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

# if (RISTRA_ENABLE_CATALYST)
#   find_package(ParaView REQUIRED COMPONENTS vtkPVPythonCatalyst)

#   message(STATUS "Found Paraview: ${ParaView_DIR}")
#   message(STATUS "IO with Paraview Catalyst enabled" )

#   include("${PARAVIEW_USE_FILE}")

#   if (NOT PARAVIEW_USE_MPI)
#     message(SEND_ERROR "ParaView must be built with MPI enabled")
#   endif()

#   list( APPEND RISTRA_LIBRARIES vtkPVPythonCatalyst vtkParallelMPI )
# endif()


if (RISTRA_ENABLE_CATALYST)
  find_package(ParaView REQUIRED)

  if (NOT TARGET ParaView::PythonCatalyst)
    message(STATUS
      "Skipping example: ${CMAKE_PROJECT_NAME} requires ParaView to be built "
      "with Catalyst and Python support enabled. Please rebuild ParaView (or "
      "point to a different build of ParaView) with PARAVIEW_USE_PYTHON set "
      "to TRUE")
    return ()
  endif()

  if (NOT PARAVIEW_USE_MPI)
    message(STATUS
      "Skipping example: ${CMAKE_PROJECT_NAME} requires ParaView to be built "
      "with MPI support enabled. Please rebuild ParaView (or point to a "
      "different build of ParaView) with PARAVIEW_USE_MPI set to TRUE")
    return ()
  endif ()

  message(STATUS "Found Paraview: ${ParaView_DIR}")
  message(STATUS "IO with Paraview Catalyst enabled" )


  list( APPEND RISTRA_LIBRARIES ParaView::PythonCatalyst VTK::CommonDataModel VTK::ParallelMPI VTK::IOParallelXML)
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

cinch_add_library_target(Ristra ristra EXPORT_TARGET RistraTargets)
cinch_target_link_libraries( Ristra ${RISTRA_LIBRARIES} )

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

set(RISTRA_LIBRARY_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR})
set(RISTRA_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/include)
set(RISTRA_CMAKE_DIR ${CMAKE_INSTALL_PREFIX}/${LIBDIR}/cmake/Ristra)

#------------------------------------------------------------------------------#
# Export targets and package.
#------------------------------------------------------------------------------#

export(
  TARGETS Ristra
  FILE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/RistraTargets.cmake
)

export(PACKAGE Ristra)

#------------------------------------------------------------------------------#
# configure .cmake file (for other projects)
#------------------------------------------------------------------------------#

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
