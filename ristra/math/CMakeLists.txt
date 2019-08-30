#~----------------------------------------------------------------------------~#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

add_unit(ristra_tuple SOURCES test/tuple.cc LIBRARIES Ristra)
add_unit(ristra_vector SOURCES test/vector.cc LIBRARIES Ristra)
add_unit(ristra_matrix SOURCES test/matrix.cc LIBRARIES Ristra)
