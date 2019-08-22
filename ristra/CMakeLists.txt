#------------------------------------------------------------------------------#
# configure header
#------------------------------------------------------------------------------#

configure_file(ristra-config.h.in ristra-config.h @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ristra-config.h DESTINATION include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

#------------------------------------------------------------------------------#
# add source subdirectories
#------------------------------------------------------------------------------#

add_subdirectory(assertions)
add_subdirectory(compatibility)
add_subdirectory(elements)
add_subdirectory(embedded)
add_subdirectory(geometry)
add_subdirectory(initialization)
add_subdirectory(io)
add_subdirectory(math)
add_subdirectory(utils)
add_library( ${PROJECT_NAME}
  $<TARGET_OBJECTS:${PROJECT_NAME}_assertions>
  $<TARGET_OBJECTS:${PROJECT_NAME}_compatibility>
  $<TARGET_OBJECTS:${PROJECT_NAME}_elements>
  $<TARGET_OBJECTS:${PROJECT_NAME}_embedded>
  $<TARGET_OBJECTS:${PROJECT_NAME}_geometry>
  $<TARGET_OBJECTS:${PROJECT_NAME}_initialization>
  $<TARGET_OBJECTS:${PROJECT_NAME}_io>
  $<TARGET_OBJECTS:${PROJECT_NAME}_math>
  $<TARGET_OBJECTS:${PROJECT_NAME}_utils>
)
