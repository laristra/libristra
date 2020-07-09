#pragma once

#ifdef RISTRA_ENABLE_CATALYST

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>

#include <mpi.h>

#include <vtkSmartPointer.h>
#include <vtkDataSet.h>
#include <vtkUnstructuredGrid.h>
#include <vtkXMLPUnstructuredGridWriter.h>
#include <vtkXMLUnstructuredGridWriter.h>
#include <vtkSOADataArrayTemplate.h>
#include <vtkCellArray.h>
#include <vtkPoints.h>
#include <vtkMPIController.h>
#include <vtkXMLPUnstructuredGridWriter.h>
#include <vtkMPIController.h>
#include <vtkPointData.h>


namespace ristra {
namespace io {
namespace vtk {


class UnstructuredGrid
{
	vtkSmartPointer<vtkXMLPUnstructuredGridWriter> writer;
	vtkSmartPointer<vtkXMLUnstructuredGridWriter> serialwriter;
	

	vtkSmartPointer<vtkPoints> pnts;
  	vtkSmartPointer<vtkCellArray> cells;
  	std::vector<vtkIdType> pointIDs;

  	int parallelOn;
  	int numOfPoints;
  	int numOfCells;

  	vtkIdType idx;

	std::stringstream log;

	int myRank, numRanks;

  public:
	UnstructuredGrid();
	UnstructuredGrid(int myRank, int numRanks);
	~UnstructuredGrid(){};

	vtkSmartPointer<vtkUnstructuredGrid> getUGrid(){ return uGrid; }
	vtkSmartPointer<vtkDataSet> getGrid(){ return uGrid; }

	vtkSmartPointer<vtkUnstructuredGrid> uGrid;

	// Topology

	// Points
	template <typename T> void addPoint(T *pointData);
	template <typename T> void setPoints(T *pointData, int numPoints, int cellType);
	void setPoints(vtkSmartPointer<vtkPoints> _pnts, vtkSmartPointer<vtkCellArray> _cells, int cellType);
	void pushPointsToGrid(int cellType);
	void pushPointsToGrid();


	// Polyhedra	
	template <typename T> void insertNextPoint(T *pointData);
	template <typename T> void insertNextPoint(T x, T y, T z);
	template <typename T> void insertNextPoints(T *pointData, int numPoints);

	template <typename T> void insertNextCell(std::vector<T> pointIDs);

	template <typename T> void setPointIDs(std::vector<T> pnts);
	void pushPointsCellsToGrid(int cellType);


	// Data
	template <typename T> void addVectorData(std::string varName, int numPoints, int type, T *data1, T *data2, T *data3);
	template <typename T> void addVectorData(std::string scalarName, int numPoints, int numComponents, int type, T *data);
	template <typename T> void addFieldData(std::string fieldName, T *data);

	template <typename T> void addScalarData(std::string varName, T *data, size_t numPoints, int type);
	template <typename T> void addVectorData(std::string varName, std::vector< std::vector<T> > data, size_t numPoints, int type);
	template <typename T> void addTensorData(std::string varName, std::vector< std::vector<T> > data, size_t numPoints, int type);


	// Writing
	void setOutputSerial(){ parallelOn = 0; }
	void writeParts(int numPieces, int startPiece, int SetEndPiece, std::string fileName);
	void write(std::string fileName, int parallel=0);

	// Cleanup
	void reset();

	// log
	std::string getLog(){ return log.str(); }
};



inline UnstructuredGrid::UnstructuredGrid()
{
	writer = vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
	serialwriter = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

	pnts = vtkSmartPointer<vtkPoints>::New();
  	cells = vtkSmartPointer<vtkCellArray>::New();

  	idx = 0;

  	numOfPoints = 0;
  	numOfCells = 0;

  	parallelOn = 1;

	putenv("VTK_SILENCE_GET_VOID_POINTER_WARNINGS=1");
}



inline UnstructuredGrid::UnstructuredGrid(int _myRank, int _numRanks)
{
	writer = vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();
	serialwriter = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
	uGrid = vtkSmartPointer<vtkUnstructuredGrid>::New();

	pnts = vtkSmartPointer<vtkPoints>::New();
  	cells = vtkSmartPointer<vtkCellArray>::New();

  	idx = 0;

  	myRank = _myRank;
  	numRanks = _numRanks;

	numOfPoints = 0;
  	numOfCells = 0;

  	parallelOn = 1;

	putenv("VTK_SILENCE_GET_VOID_POINTER_WARNINGS=1");
}



//
// Topology


template <typename T> 
inline void UnstructuredGrid::setPointIDs(std::vector<T> pnts)
{
	for (int i=0; i<pnts.size(); i++)
	{
		pointIDs.push_back(pnts[i]);
	}
}


template <typename T> 
inline void UnstructuredGrid::insertNextPoint(T x, T y, T z)
{
	pnts->InsertNextPoint(x, y, z);
	numOfPoints++;
}

template <typename T> 
inline void UnstructuredGrid::insertNextPoint(T *pointData)
{
	pnts->InsertNextPoint(pointData[0],pointData[1],pointData[2]);
	numOfPoints++;
}


template <typename T> 
inline void UnstructuredGrid::insertNextPoints(T *pointData, int numPoints)
{
	for (int i=0; i<numPoints ; ++i)
	{
		T pnt[3];
		pnt[0] = pointData[i*3 + 0];
		pnt[1] = pointData[i*3 + 1];
		pnt[2] = pointData[i*3 + 2];

		pnts->InsertNextPoint(pnt[0],pnt[1],pnt[2]);
		numOfPoints++;

	}
}



template <typename T> 
inline void UnstructuredGrid::addPoint(T *pointData)
{
	pnts->InsertPoint(idx, pointData);
    cells->InsertNextCell(1, &idx);
    idx++;
}







template <typename T> 
inline void UnstructuredGrid::setPoints(T *pointData, int numPoints, int cellType)
{
	pnts->SetNumberOfPoints(numPoints);

	for (int i=0; i<numPoints ; ++i)
	{
		T pnt[3];
		pnt[0] = pointData[i*3 + 0];
		pnt[1] = pointData[i*3 + 1];
		pnt[2] = pointData[i*3 + 2];

		pnts->SetPoint(i, pnt[0],pnt[1],pnt[2]);
		cells->InsertNextCell(1, &idx);
		idx++;
	}

	pushPointsToGrid(cellType);
}


inline void UnstructuredGrid::setPoints(vtkSmartPointer<vtkPoints> _pnts, vtkSmartPointer<vtkCellArray> _cells, int cellType)
{
	uGrid->SetPoints(_pnts);
	uGrid->SetCells(cellType, _cells);
}


template <typename T> 
inline void UnstructuredGrid::insertNextCell(std::vector<T> pointIDs)
{
	int numPoints = pointIDs.size();
	vtkIdType *face = new vtkIdType[numPoints];

	for (int i=0; i<numPoints; i++)
		face[i] = pointIDs[i];

	cells->InsertNextCell(numPoints, face);
	 numOfCells++;

	if (face != NULL)
		delete []face;
	face = NULL;

}


inline void UnstructuredGrid::pushPointsCellsToGrid(int cellType)
{
	//uGrid->SetPoints(pnts);
	std::cout << "numOfPoints: " << numOfPoints << std::endl;
	std::cout << "numOfCells: " << numOfCells << std::endl;
	//uGrid->InsertNextCell(cellType, numOfPoints, &pointIDs[0], numOfCells, cells->GetPointer());
	//uGrid->InsertNextCell(cellType, numOfPoints, &pointIDs[0], numOfCells, &cells[0]);
}


inline void UnstructuredGrid::pushPointsToGrid(int cellType)
{
	uGrid->SetPoints(pnts);
	uGrid->SetCells(cellType, cells);
}


inline void UnstructuredGrid::pushPointsToGrid()
{
	uGrid->SetPoints(pnts);
}


inline void UnstructuredGrid::reset()
{
	pnts->Delete();
	cells->Delete();

	idx = 0;
}


// Attributes
template <typename T>
inline void UnstructuredGrid::addFieldData(std::string fieldName, T *data)
{
  	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfTuples(1);
  	temp->SetNumberOfComponents(1);
  	temp->SetName(fieldName.c_str());
  	temp->SetArray(0, data, 1, false, true);
  	uGrid->GetFieldData()->AddArray(temp);

  	temp->Delete();
}



template <typename T>
inline void UnstructuredGrid::addVectorData(std::string varName, int numPoints, int type, T *data1, T *data2, T *data3)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents(3);
  	temp->SetName(varName.c_str());


  	// Works
   	for(int i=0; i<numPoints; i++)
	{
	 	temp->InsertNextValue(data1[i]);
		temp->InsertNextValue(data2[i]);
		temp->InsertNextValue(data3[i]); 
	}


  	if (type == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}




//GetCellData()->Add Array garbage data
//https://public.kitware.com/pipermail/paraview-developers/2016-September/004665.html
//
// Data
template <typename T>
inline void UnstructuredGrid::addScalarData(std::string varName, T *data, size_t numElements, int discretization)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents(1);
  	temp->SetName(varName.c_str());


  	// DOES NOT WORk!!!!
  	// temp->SetArray(0, data, numElements, 1, true); // DOES NOT WORk!!!!

  	// Works
   	for(size_t i=0; i<numElements; i++)
	 	temp->InsertNextValue(data[i]);


  	if (discretization == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}


template <typename T>
inline void UnstructuredGrid::addVectorData(std::string varName, std::vector< std::vector<T> > data, size_t numElements, int discretization)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents( data.size() );
  	temp->SetName(varName.c_str());

  	for (size_t i=0; i<numElements; i++)
		for (int n=0; n<data.size(); n++)
			temp->InsertNextValue(data[n][i]);

  	if (discretization == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}


template <typename T>
inline void UnstructuredGrid::addTensorData(std::string varName, std::vector< std::vector<T> > data, size_t numElements, int discretization)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents( data.size() );
  	temp->SetName(varName.c_str());

	for (size_t i=0; i<numElements; i++)
		for (int n=0; n<data.size(); n++)
			temp->InsertNextValue(data[n][i]);

  	if (discretization == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}




template <typename T>
inline void UnstructuredGrid::addVectorData(std::string varName, int numPoints, int numComponents, int type, T *data)
{
	vtkAOSDataArrayTemplate<T>* temp = vtkAOSDataArrayTemplate<T>::New();

	temp->SetNumberOfTuples(numPoints);
  	temp->SetNumberOfComponents(numComponents);
  	temp->SetName(varName.c_str());
  	temp->SetArray(data, numPoints*numComponents, false, true);

  	if (type == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);

  	temp->Delete();
}



//
// Writing
inline void UnstructuredGrid::writeParts(int numPieces, int startPiece, int endPiece, std::string fileName)
{
	if (parallelOn)
	{
		writer->SetNumberOfPieces(numPieces);
		writer->SetStartPiece(startPiece);
		writer->SetEndPiece(endPiece);
	}

	write(fileName, parallelOn);
}


inline void UnstructuredGrid::write(std::string fileName, int parallel)
{
	std::string outputFilename;


	if (parallel == 1)
	{
		writer->SetDataModeToBinary();
    	writer->SetCompressor(nullptr);

		auto contr = vtkSmartPointer<vtkMPIController>::New();
		contr->Initialize(NULL, NULL, 1);
		contr->SetGlobalController(contr);

		outputFilename = fileName + ".pvtu";

		writer->SetController(contr);


		writer->SetFileName(outputFilename.c_str());

		#if VTK_MAJOR_VERSION <= 5
	        writer->SetInput(uGrid);
	    #else
	        writer->SetInputData(uGrid);
	    #endif

		writer->Write();

		//contr->Finalize();
	}
	else
	{
		outputFilename = fileName + ".vtu";
		
		serialwriter->SetDataModeToBinary();
    	serialwriter->SetCompressor(nullptr);

		serialwriter->SetFileName(outputFilename.c_str());

		#if VTK_MAJOR_VERSION <= 5
	        serialwriter->SetInput(uGrid);
	    #else
	        serialwriter->SetInputData(uGrid);
	    #endif

		serialwriter->Write();

	}
}


// Data
template <typename T>
inline void addScalarData(std::string varName, T *data, size_t numPoints, int type, vtkSmartPointer<vtkUnstructuredGrid> & uGrid)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents(1);
  	temp->SetName(varName.c_str());


  	// DOES NOT WORk!!!!
  	// temp->SetArray(0, data, numPoints, 1, true); // DOES NOT WORk!!!!

  	// Works
   	for(size_t i=0; i<numPoints; i++)
	 	temp->InsertNextValue(data[i]);


  	if (type == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}


template <typename T>
inline void addTensorData(std::string varName, std::vector< std::vector<T> > data, size_t numPoints, int type, vtkSmartPointer<vtkUnstructuredGrid> & uGrid)
{
	vtkSOADataArrayTemplate<T>* temp = vtkSOADataArrayTemplate<T>::New();

  	temp->SetNumberOfComponents( data.size() );
  	temp->SetName(varName.c_str());

	for (size_t i=0; i<numPoints; i++)
		for (int n=0; n<data.size(); n++)
			temp->InsertNextValue(data[n][i]);

  	if (type == 0) // point
  		uGrid->GetPointData()->AddArray(temp);
  	else
  		uGrid->GetCellData()->AddArray(temp);
}



inline void writeUnstructuredGrid(std::string fileName, 
	vtkSmartPointer<vtkUnstructuredGrid> uGrid, int numPieces, int startPiece, int endPiece)
{
	if (numPieces > 1)
	{
		std::string outputFilename = fileName + ".pvtu";
			
		vtkSmartPointer<vtkXMLPUnstructuredGridWriter> writer =  vtkSmartPointer<vtkXMLPUnstructuredGridWriter>::New();

		writer->SetNumberOfPieces(numPieces);
		writer->SetStartPiece(startPiece);
		writer->SetEndPiece(endPiece);

		writer->SetDataModeToBinary();
    	writer->SetCompressor(nullptr);

		auto contr = vtkSmartPointer<vtkMPIController>::New();
		contr->Initialize(NULL, NULL, 1);
		contr->SetGlobalController(contr);

		writer->SetController(contr);

		writer->SetFileName(outputFilename.c_str());

		#if VTK_MAJOR_VERSION <= 5
	        writer->SetInput(uGrid);
	    #else
	        writer->SetInputData(uGrid);
	    #endif

		writer->Write();

		//contr->Finalize();
	}
	else
	{
		std::string outputFilename = fileName + ".vtu";

		vtkSmartPointer<vtkXMLUnstructuredGridWriter> serialwriter = vtkSmartPointer<vtkXMLUnstructuredGridWriter>::New();
		
		serialwriter->SetDataModeToBinary();
    	serialwriter->SetCompressor(nullptr);

		serialwriter->SetFileName(outputFilename.c_str());

		#if VTK_MAJOR_VERSION <= 5
	        serialwriter->SetInput(uGrid);
	    #else
	        serialwriter->SetInputData(uGrid);
	    #endif

		serialwriter->Write();

	}

	std::cout << "Wrote out data!" << std::endl;
}



} // end of vtk namespace
} // end of io namespace
} // end of ristra namespace

#endif
