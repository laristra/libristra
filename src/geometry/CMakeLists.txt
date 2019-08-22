#~----------------------------------------------------------------------------~#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

set(geometry_HEADERS
  area.h      detail/area_impl.h
  centroid.h  detail/centroid_impl.h
  normal.h
  point.h
  shapes/geometric_shapes.h
  shapes/hexahedron.h
  shapes/polygon.h
  shapes/polyhedron.h
  shapes/quadrilateral.h
  shapes/tetrahedron.h
  shapes/triangle.h
  space_vector.h
  PARENT_SCOPE
)

set(geometry_SOURCES
  PARENT_SCOPE
)

cinch_add_unit(ristra_centroid SOURCES test/centroid.cc )
cinch_add_unit(ristra_point SOURCES test/point.cc )
cinch_add_unit(ristra_shapes SOURCES shapes/test/shapes.cc )
cinch_add_unit(ristra_space_vector SOURCES test/space_vector.cc )

#~---------------------------------------------------------------------------~-#
# Formatting options
# vim: set tabstop=2 shiftwidth=2 expandtab :
#~---------------------------------------------------------------------------~-#
