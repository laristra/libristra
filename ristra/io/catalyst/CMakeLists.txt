set(Adaptor_SRCS "flecsaleAdaptor.cc")
add_library(catalystadaptor ${Adaptor_SRCS})
#target_link_libraries(catalystadaptor vtkPVPythonCatalyst vtkParallelMPI)

if (NOT PARAVIEW_USE_MPI)
  message(FATAL_ERROR "ParaView must be built with MPI enabled")
endif()

#include(vtkModuleMacros)
#include(vtkMPI)
