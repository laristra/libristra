#~----------------------------------------------------------------------------~#
# Copyright (c) 2016 Los Alamos National Laboratory, LLC
# All rights reserved
#~----------------------------------------------------------------------------~#

ristra_add_unit(ristra_centroid SOURCES test/centroid.cc LIBRARIES Ristra)
ristra_add_unit(ristra_point SOURCES test/point.cc LIBRARIES Ristra)
ristra_add_unit(ristra_shapes SOURCES shapes/test/shapes.cc LIBRARIES Ristra)
ristra_add_unit(ristra_space_vector SOURCES test/space_vector.cc LIBRARIES Ristra)
