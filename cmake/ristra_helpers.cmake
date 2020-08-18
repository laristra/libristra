set(DIR_OF_RISTRA_CMAKE ${CMAKE_CURRENT_LIST_DIR})  

function (ristra_add_unit name)
  if (NOT CMAKE_TESTING_ENABLED)
    return()
  endif()

	MESSAGE( STATUS "Creating test ${name}" )
  set(multi_value_args
    SOURCES LIBRARIES INPUTS
  )
  cmake_parse_arguments(unit
    "${options}" "${one_value_args}" "${multi_value_args}" ${ARGN})

	add_executable(${name} ${unit_SOURCES} ${DIR_OF_RISTRA_CMAKE}/ristra_unit.cc)
  target_link_libraries(${name} ${unit_LIBRARIES} gtest)
  target_include_directories(${name} PRIVATE ${GTEST_DIR}/googletest/include)

  foreach(input ${unit_INPUTS})
     get_filename_component(_basename ${input} NAME)
    configure_file(${input} ${CMAKE_CURRENT_BINARY_DIR}/${_basename} COPYONLY)
  endforeach()

  add_test( NAME ${name} COMMAND $<TARGET_FILE:${name}> )
	
endfunction()
