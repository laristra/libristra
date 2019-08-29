#------------------------------------------------------------------------------#
# configure header
#------------------------------------------------------------------------------#

configure_file(ristra-config.h.in ristra-config.h @ONLY)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#------------------------------------------------------------------------------#
# add source subdirectories
#------------------------------------------------------------------------------#

add_library( ${PROJECT_NAME}
  # top level config
  ${CMAKE_CURRENT_BINARY_DIR}/ristra-config.h
  # assertions
  assertions/dbc.h
  assertions/dbc_impl.h
  assertions/errors.h
  assertions/exceptions.h
  assertions/here.h
  assertions/dbc_impl.cc
  # compatibility
  compatibility/type_traits.h
  # eleements
  elements/elements.h
  elements/utilities.h
  elements/elements.cc
  # embedded
  embedded/embed_lua.h
  embedded/embed_python.h
  # geometry
  geometry/area.h
  geometry/area_impl.h
  geometry/centroid.h
  geometry/centroid_impl.h
  geometry/normal.h
  geometry/point.h
  geometry/shapes/geometric_shapes.h
  geometry/shapes/hexahedron.h
  geometry/shapes/polygon.h
  geometry/shapes/polyhedron.h
  geometry/shapes/quadrilateral.h
  geometry/shapes/tetrahedron.h
  geometry/shapes/triangle.h
  geometry/space_vector.h
  # initialization
  initialization/announce.h
  initialization/inputs_impl.h
  initialization/init_value.h
  initialization/input_engine.h
  initialization/input_source.h
  initialization/announce.cc
  # io
  io/catalyst/adaptor.h
  io/vtk.h
  io/write_binary.h
  io/vtk.cc
  # math
  math/array.h
  math/constants.h
  math/general_impl.h
  math/general.h
  math/matrix.h
  math/multi_array.h
  math/tuple.h
  math/vector.h
  # utils
  utils/algorithm.h
  utils/array_ref.h
  utils/array_view.h
  utils/array_view_impl.h
  utils/const_string.h
  utils/dimensioned_array.h
  utils/filter_iterator.h
  utils/fixed_vector.h
  utils/functional.h
  utils/static_for.h
  utils/string_utils.h
  utils/static_warning.h
  utils/tasks.h
  utils/template_helpers.h
  utils/template_helpers_impl.h
  utils/time_utils.h
  utils/trivial_string.h
  utils/tuple_for_each.h
  utils/tuple_for_each_impl.h
  utils/tuple_to_array.h
  utils/tuple_visit.h
  utils/tuple_visit_impl.h
  utils/tuple_zip.h
  utils/tuple_zip_impl.h
  utils/type_traits.h
  utils/type_traits_impl.h
  utils/zip.h
  utils/zip_impl.h

)

# for testing
add_subdirectory(assertions)
#add_subdirectory(compatibility)
add_subdirectory(elements)
add_subdirectory(embedded)
add_subdirectory(geometry)
add_subdirectory(initialization)
#add_subdirectory(io)
add_subdirectory(math)
add_subdirectory(utils)

# now get headers to install
get_target_property( _sources ${PROJECT_NAME} SOURCES)
list(FILTER _sources INCLUDE REGEX "(.+).h")

#foreach(_file ${_sources})
#  get_filename_component(_path ${_file} PATH)
#  if ( IS_ABSOLUTE ${_file} )
#    string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}" "" _path ${_path})
#    string(REPLACE "${CMAKE_CURRENT_BINARY_DIR}" "" _path ${_path})
#  endif()
#  install(FILES ${_file} DESTINATION include/ristra/${_path} )
#endforeach()
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h" )

target_link_libraries( ${PROJECT_NAME} ${RISTRA_LIBRARIES} )
