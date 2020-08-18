#------------------------------------------------------------------------------#
# configure header
#------------------------------------------------------------------------------#

configure_file(ristra-config.h.in ristra-config.h @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ristra-config.h DESTINATION include/ristra)

#------------------------------------------------------------------------------#
# add source subdirectories
#------------------------------------------------------------------------------#


# for testing
add_subdirectory(assertions)
#add_subdirectory(compatibility)
add_subdirectory(elements)
add_subdirectory(embedded)
add_subdirectory(geometry)
add_subdirectory(initialization)
add_subdirectory(io)
add_subdirectory(math)
add_subdirectory(utils)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} DESTINATION include FILES_MATCHING PATTERN "*.h" )
