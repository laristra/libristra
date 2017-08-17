#~----------------------------------------------------------------------------~#
#
# TO DO: awesome Ristra ascii art here
#
#
# Copyright (c) 2017 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

#------------------------------------------------------------------------------#
# Create user guide header with version information
#------------------------------------------------------------------------------#

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_ug_header.tex.in
    ${CMAKE_BINARY_DIR}/doc/ristra_ug_header.tex)

#------------------------------------------------------------------------------#
# Pandoc options for user guide
#------------------------------------------------------------------------------#

set(ug_pandoc_options
    "--toc"
    "--include-in-header=${CMAKE_SOURCE_DIR}/cinch/tex/addtolength.tex"
    "--include-in-header=${CMAKE_BINARY_DIR}/doc/ristra_ug_header.tex"
    "--include-in-header=${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_ug_title.tex"
    "--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/maketitle.tex"
    "--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/firstpageempty.tex"
    "--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/titlebreak.tex"
)

#------------------------------------------------------------------------------#
# Add user guide target
#------------------------------------------------------------------------------#

cinch_add_doc(user-guide ristra_ug.py ristra
    ristra-user-guide-${${PROJECT_NAME}_VERSION}.pdf
    PANDOC_OPTIONS ${ug_pandoc_options} IMAGE_GLOB "*.pdf"
)

#------------------------------------------------------------------------------#
# Create developer guide header with version information
#------------------------------------------------------------------------------#

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_dg_header.tex.in
    ${CMAKE_BINARY_DIR}/doc/ristra_dg_header.tex
)

#------------------------------------------------------------------------------#
# Pandoc options for developer guide
#------------------------------------------------------------------------------#

set(dg_pandoc_options
    "--toc"
    "--include-in-header=${CMAKE_SOURCE_DIR}/cinch/tex/addtolength.tex"
    "--include-in-header=${CMAKE_BINARY_DIR}/doc/ristra_dg_header.tex"
    "--include-before-body=${CMAKE_CURRENT_SOURCE_DIR}/doc/ristra_dg_title.tex"
    "--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/firstpageempty.tex"
    #"--include-before-body=${CMAKE_SOURCE_DIR}/cinch/tex/titlebreak.tex"
)

set(dg_image_list
  "${CMAKE_SOURCE_DIR}/doc/medium-ristra.png"
)

#------------------------------------------------------------------------------#
# Add developer guide target
#------------------------------------------------------------------------------#

cinch_add_doc(developer-guide ristra_dg.py ristra
    ristra-developer-guide-${${PROJECT_NAME}_VERSION}.pdf
    PANDOC_OPTIONS ${dg_pandoc_options} IMAGE_GLOB "*.pdf"
    IMAGE_LIST ${dg_image_list}
)

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
