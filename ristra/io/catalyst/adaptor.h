/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
/// \brief Functions to write binary files in vtk format.
///
////////////////////////////////////////////////////////////////////////////////
#pragma once

// configuration include
#include "ristra-config.h"

#ifdef RISTRA_ENABLE_CATALYST

// vtk includes
#include <vtkCPDataDescription.h>
#include <vtkCPInputDataDescription.h>
#include <vtkCPProcessor.h>
#include <vtkCPPythonScriptPipeline.h>
#include <vtkCellData.h>
#include <vtkCellType.h>
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCPDataDescription.h>
#include <vtkCPInputDataDescription.h>
#include <vtkMPIController.h>
#include <vtkMultiProcessController.h>

// system includes
#include <iostream>
#include <string>
#include <vector>

namespace ristra {
namespace io {
namespace catalyst {


inline vtkCPProcessor* initAdaptor(std::vector<std::string> scripts)
{
	//MPI_Init(NULL,NULL); 
	int rank, nprocs;

  //MPI_Init(&argc,&argv); 
  MPI_Comm_size(MPI_COMM_WORLD,&nprocs); 
  MPI_Comm_rank(MPI_COMM_WORLD,&rank); 

  vtkCPProcessor* processor_ = nullptr;
  processor_ = vtkCPProcessor::New();
  processor_->Initialize();


  //for (const auto & script : scripts)
  for (int i=0; i<scripts.size(); i++)
  {
    vtkNew<vtkCPPythonScriptPipeline> pipeline;
    pipeline->Initialize(scripts[i].c_str());
    processor_->AddPipeline(pipeline.GetPointer());
  }

  return processor_;
}



inline void processCatalyst(vtkCPProcessor* processor_, vtkUnstructuredGrid * grid, double time, unsigned int timeStep, bool lastTimeStep) 
{
  vtkNew<vtkCPDataDescription> dataDescription;
  dataDescription->AddInput("input");
  dataDescription->SetTimeData(time, timeStep);

  if (lastTimeStep == true)
  {
    // assume that we want to all the pipelines to execute if it
    // is the last time step.
    dataDescription->ForceOutputOn();
  }

  dataDescription->ForceOutputOn();

  // determine if any coprocessing needs to be done at this TimeStep/Time
  auto do_coprocessing = processor_->RequestDataDescription(dataDescription.GetPointer()); 
  if (do_coprocessing)
  {
    dataDescription->GetInputDescriptionByName("input")->SetGrid(grid);
    processor_->CoProcess(dataDescription.GetPointer());
  }
}


inline vtkCPProcessor* finalizeAdaptor(vtkCPProcessor* processor)
{
  if (processor)
  {
    processor->Delete();
    processor = NULL;
  }
}



class adaptor_t {

  vtkCPProcessor* processor_ = nullptr;

public:

  adaptor_t(const std::vector<std::string> & scripts)
  {
		processor_ = vtkCPProcessor::New();
		processor_->Initialize();

	  for (const auto & script : scripts)
	  {
	  	vtkNew<vtkCPPythonScriptPipeline> pipeline;
	  	pipeline->Initialize(script.c_str());
	  	processor_->AddPipeline(pipeline.GetPointer());
	  }
  }


  ~adaptor_t()
  {
	  if (processor_)
	  {
		  processor_->Delete();
		  processor_ = nullptr;
	  }
  }
  
  void process( 
    vtkUnstructuredGrid * grid, 
    double time, 
    unsigned int timeStep, 
    bool lastTimeStep 
  ) {
  
	  vtkNew<vtkCPDataDescription> dataDescription;
	  dataDescription->AddInput("input");
	  dataDescription->SetTimeData(time, timeStep);

	  if (lastTimeStep == true)
	  {
		  // assume that we want to all the pipelines to execute if it
		  // is the last time step.
		 dataDescription->ForceOutputOn();
	  }

    // determine if any coprocessing needs to be done at this TimeStep/Time
    auto do_coprocessing = 
      processor_->RequestDataDescription(dataDescription.GetPointer()); 
	  if (do_coprocessing)
    {
		  dataDescription->GetInputDescriptionByName("input")->SetGrid(grid);
      processor_->CoProcess(dataDescription.GetPointer());
    }

  }

};


} // end of ristra namespace
} // end of io namespace
} // end of Catalyst namespace


#endif // RISTRA_ENABLE_CATALYST
