#pragma once

#ifdef RISTRA_ENABLE_CATALYST

// user includes
#include <flecsi/topology/mesh_utils.h>
#include <ristra/utils/time_utils.h>
#include <ristra/io/catalyst/vtk/unstructuredGrid.h>


// system includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <utility>


// vtk includes
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkCellType.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>
#include <vtkUnstructuredGridWriter.h>
#include <vtkUnstructuredGridReader.h>

#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkIntArray.h>
#include <vtkLongArray.h>
#include <vtkLongLongArray.h>

namespace ristra {
namespace io {
namespace catalyst {

//using namespace apps::hydro;

using mesh_t = flecsi_sp::burton::burton_mesh_t;
using real_t = mesh_t::real_t;
using vector_t = mesh_t::vector_t;



// Base template from flescale/ale/mesh/vtk_utils.h
template< typename T >
struct vtk_array_t {};


template<>
struct vtk_array_t<float>
{ 
  	using type = vtkFloatArray;
};

template<>
struct vtk_array_t<double>
{ 
  	using type = vtkDoubleArray;
};

template<>
struct vtk_array_t<int>
{ 
  	using type = vtkIntArray;
};

template<>
struct vtk_array_t<long>
{ 
  	using type = vtkLongArray;
};

template<>
struct vtk_array_t<long long>
{ 
  	using type = vtkLongLongArray;
};


// a lambda function for validating strings
auto validate_string = []( auto && str ) 
{
	return std::forward<decltype(str)>(str);
};


inline void initVTKUnstructuredGrid(vtkSmartPointer<vtkUnstructuredGrid> grid)
{
	grid = vtkSmartPointer<vtkUnstructuredGrid>::New();
}


template< typename T >
inline void writePointsToGrid(T & mesh, vtkSmartPointer<vtkUnstructuredGrid> grid)
{

	auto points = vtkPoints::New();
	points->SetNumberOfPoints( mesh.num_vertices() );

	for ( auto v : mesh.vertices() ) 
	{
		auto id = v.id();
		auto & coord = v->coordinates();
		double xyz[3] = {0, 0, 0};
		std::copy(coord.begin(), coord.end(), xyz);
		points->SetPoint(id, xyz);
	}

	// transfer the points
	grid->SetPoints(points);
	points->Delete();
}


template< typename T >
inline void writeCellsToGrid(T & mesh, vtkSmartPointer<vtkUnstructuredGrid> grid)
{
	for ( auto c : mesh.cells() ) 
	{
	    // get the vertices in this cell
	    auto cell_verts = mesh.vertices(c);
	    auto num_cell_verts = cell_verts.size();

	    // copy them to the vtk type
	    std::vector< vtkIdType > vert_ids(num_cell_verts);
	    std::transform( cell_verts.begin(), cell_verts.end(), vert_ids.begin(), [](auto && v) { return v.id(); } );

	    // get the faces
	    auto cell_faces = mesh.faces(c);
	    auto num_cell_faces = cell_faces.size();

	    // get the total number of vertices
	    auto tot_verts = std::accumulate( 
	      	cell_faces.begin(), cell_faces.end(), static_cast<size_t>(0),
	      	[&mesh](auto sum, auto f) { return sum + mesh.vertices(f).size(); }
	    );

	    // the list of faces that vtk requires contains the number of points in each
	    // face AND the point ids themselves.
	    std::vector< vtkIdType > face_data;
	    face_data.reserve( tot_verts + num_cell_faces );
	    for ( auto f : cell_faces ) 
	    {
	    	auto face_cells = mesh.cells(f);
	      	auto face_verts = mesh.vertices(f);
	      	auto num_face_verts = face_verts.size();

	      	// copy the face vert ids to the vtk type
	      	std::vector< vtkIdType > face_vert_ids( num_face_verts );
	      	std::transform( 
	        	face_verts.begin(), face_verts.end(), face_vert_ids.begin(),
	        	[](auto && v) { return v.id(); } 
	      	);
	      
	      	// check the direction of the vertices
	      	if ( face_cells[0] != c ) 
	        	std::reverse( face_vert_ids.begin(), face_vert_ids.end() );
	      
	      	// now copy them to the global array
	      	face_data.emplace_back( num_face_verts );
	      	for ( auto v : face_vert_ids )
	        	face_data.emplace_back( v );
	    }

	    
	    // set the cell vertices
	    grid->InsertNextCell(
	      VTK_POLYHEDRON, num_cell_verts, vert_ids.data(),
	      num_cell_faces, face_data.data()
	    );
	}
}



inline void outputVTKUnstructredGrid(std::string filename, vtkSmartPointer<vtkUnstructuredGrid> grid)
{
	// For debugging: Will output an unstructured grid to dsik for debug
	vtkUnstructuredGridWriter *writer = vtkUnstructuredGridWriter::New();
	writer->SetInputDataObject(grid);
	writer->SetFileTypeToBinary();
	writer->SetFileName(filename.c_str());
	writer->Write();
}


inline void outputFile(std::string filename, std::string content)
{
	// For debugging: Will output info from a string as a file for debugging
	ofstream myfile(filename.c_str());
  	if (myfile.is_open())
  	{
    	myfile << content;
    	myfile.close();
  	}
  	else 
  		cout << "Unable to open file " << filename << std::endl;;
}



template< typename T > 
inline vtkSmartPointer<vtkUnstructuredGrid> populate(
	mesh_t &m, std::vector<T * > &var_vec, std::vector<std::string> &varname)
{
	// Create a mesh for single material

    // mesh statistics
    // get the general statistics
    constexpr auto num_dims = mesh_t::num_dimensions;
    auto num_nodes = m.num_vertices();
    auto num_faces = num_dims==3 ? m.num_faces() : 0;
    auto num_elems = m.num_cells();
    auto num_elem_blk = 1;
    auto num_node_sets = 0;
    auto num_side_sets = 0;
    using  ex_real_t  = real_t;



    //--------------------------------------------------------------------------
    // Create structure
    //--------------------------------------------------------------------------

    ristra::io::vtk::UnstructuredGrid temp;
	

    //--------------------------------------------------------------------------
    // Point Coordinates
    //--------------------------------------------------------------------------

    std::vector<real_t> vertex_coord( num_nodes * num_dims );
    std::vector<int> pointIDs;
    for (auto v : m.vertices()) 
    {
    	auto & coords = v->coordinates();

    	pointIDs.push_back(v.id());

    	std::vector<float> vertex;
    	int count = 0;
      	for ( int i=0; i<num_dims; i++ )
      	{
      		vertex_coord[ v.id()*3 + i] = coords[i];
      		vertex.push_back(coords[i]);
      		count++;
      	}
      	if (num_dims == 2)
      		vertex.push_back(0.0);

      	temp.insertNextPoint(&vertex[0]);
    }

    temp.setPointIDs(pointIDs);


    

    //--------------------------------------------------------------------------
    // Face connectivity
    //-------------------------------------------------------------------------- 
	const auto & owned_cells = m.cells(flecsi::owned);
	auto num_owned_cells = owned_cells.size();
	auto num_cells = m.cells().size();
	std::vector< bool > is_ghost_cell( num_cells, true );
	for ( auto c : owned_cells ) 
		is_ghost_cell[c.id()] = false;

	// 	  // some mesh parameters
	//   const auto & cells = mesh.cells();
	//   const auto & owned_cells = mesh.cells(flecsi::owned);
	//   auto num_cells = cells.size();
	//   auto num_owned_cells = owned_cells.size();

	for ( auto c : m.cells() ) 
	{
		if ( is_ghost_cell[c] )	// Skip ghost cells
			continue;

	    // get the vertices in this cell
	    auto cell_verts = m.vertices(c);
	    auto num_cell_verts = cell_verts.size();

	    // copy them to the vtk type
	    std::vector< vtkIdType > vert_ids(num_cell_verts);
	    std::transform( cell_verts.begin(), cell_verts.end(), vert_ids.begin(), [](auto && v) { return v.id(); } );

	    // get the faces
	    auto cell_faces = m.faces(c);
	    auto num_cell_faces = cell_faces.size();

	    // get the total number of vertices
	    auto tot_verts = std::accumulate( 
	      	cell_faces.begin(), cell_faces.end(), static_cast<size_t>(0),
	      	[&m](auto sum, auto f) { return sum + m.vertices(f).size(); }
	    );

	    // the list of faces that vtk requires contains the number of points in each
	    // face AND the point ids themselves.
	    std::vector< vtkIdType > face_data;
	    face_data.reserve( tot_verts + num_cell_faces );
	    for ( auto f : cell_faces ) 
	    {
	    	auto face_cells = m.cells(f);
	      	auto face_verts = m.vertices(f);
	      	auto num_face_verts = face_verts.size();

	      	// copy the face vert ids to the vtk type
	      	std::vector< vtkIdType > face_vert_ids( num_face_verts );
	      	std::transform( 
	        	face_verts.begin(), face_verts.end(), face_vert_ids.begin(),
	        	[](auto && v) { return v.id(); } 
	      	);
	      
	      	// check the direction of the vertices
	      	if ( face_cells[0] != c ) 
	        	std::reverse( face_vert_ids.begin(), face_vert_ids.end() );
	      
	      	// now copy them to the global array
	      	face_data.emplace_back( num_face_verts );
	      	for ( auto v : face_vert_ids )
	        	face_data.emplace_back( v );
	    }

	    
	    // set the cell vertices
	    temp.uGrid->InsertNextCell(
	      VTK_POLYHEDRON, num_cell_verts, vert_ids.data(),
	      num_cell_faces, face_data.data()
	    );
	}


    temp.pushPointsToGrid();



    //--------------------------------------------------------------------------
    // Write Fields
    //--------------------------------------------------------------------------

    static int count = 0;
  	for (int i=0; i<var_vec.size(); ++i)
    {
        const T& f = *var_vec[i];
        std::vector<float> data;
        for(auto c: m.cells())
            data.push_back(f(c));
        
		temp.addScalarData(varname[i].c_str(), &data[0], m.num_cells(), 1);
    }
    count++;

	return temp.getUGrid();
}


//template< typename T > 
inline vtkSmartPointer<vtkUnstructuredGrid> populate_mm(
	mesh_t &m, std::vector< std::vector<real_t> > &var_vec, std::vector<std::string> &varname)
{
	// Create a mesh for multiple material

    // mesh statistics
    // get the general statistics
    constexpr auto num_dims = mesh_t::num_dimensions;
    auto num_nodes = m.num_vertices();
    auto num_faces = num_dims==3 ? m.num_faces() : 0;
    auto num_elems = m.num_cells();
    auto num_elem_blk = 1;
    auto num_node_sets = 0;
    auto num_side_sets = 0;
    using  ex_real_t  = real_t;



    //--------------------------------------------------------------------------
    // Create structure
    //--------------------------------------------------------------------------

    ristra::io::vtk::UnstructuredGrid temp;




    //--------------------------------------------------------------------------
    // Point Coordinates
    //--------------------------------------------------------------------------

    std::vector<real_t> vertex_coord( num_nodes * num_dims );
    std::vector<int> pointIDs;
    for (auto v : m.vertices()) 
    {
    	auto & coords = v->coordinates();

    	pointIDs.push_back(v.id());

    	std::vector<float> vertex;
    	int count = 0;
      	for ( int i=0; i<num_dims; i++ )
      	{
      		vertex_coord[ v.id()*3 + i] = coords[i];
      		vertex.push_back(coords[i]);
      		count++;
      	}
      	if (num_dims == 2)
      		vertex.push_back(0.0);

      	temp.insertNextPoint(&vertex[0]);
    }

    temp.setPointIDs(pointIDs);


    
    //--------------------------------------------------------------------------
    // Face connectivity
    //-------------------------------------------------------------------------- 

	const auto & owned_cells = m.cells(flecsi::owned);
	auto num_owned_cells = owned_cells.size();
	auto num_cells = m.cells().size();
	std::vector< bool > is_ghost_cell( num_cells, true );
	for ( auto c : owned_cells ) 
		is_ghost_cell[c.id()] = false;


	for ( auto c : m.cells() ) 
	{
		if ( is_ghost_cell[c] )	// Skip ghost cells
			continue;

	    // get the vertices in this cell
	    auto cell_verts = m.vertices(c);
	    auto num_cell_verts = cell_verts.size();

	    // copy them to the vtk type
	    std::vector< vtkIdType > vert_ids(num_cell_verts);
	    std::transform( cell_verts.begin(), cell_verts.end(), vert_ids.begin(), [](auto && v) { return v.id(); } );

	    // get the faces
	    auto cell_faces = m.faces(c);
	    auto num_cell_faces = cell_faces.size();

	    // get the total number of vertices
	    auto tot_verts = std::accumulate( 
	      	cell_faces.begin(), cell_faces.end(), static_cast<size_t>(0),
	      	[&m](auto sum, auto f) { return sum + m.vertices(f).size(); }
	    );

	    // the list of faces that vtk requires contains the number of points in each
	    // face AND the point ids themselves.
	    std::vector< vtkIdType > face_data;
	    face_data.reserve( tot_verts + num_cell_faces );
	    for ( auto f : cell_faces ) 
	    {
	    	auto face_cells = m.cells(f);
	      	auto face_verts = m.vertices(f);
	      	auto num_face_verts = face_verts.size();

	      	// copy the face vert ids to the vtk type
	      	std::vector< vtkIdType > face_vert_ids( num_face_verts );
	      	std::transform( 
	        	face_verts.begin(), face_verts.end(), face_vert_ids.begin(),
	        	[](auto && v) { return v.id(); } 
	      	);
	      
	      	// check the direction of the vertices
	      	if ( face_cells[0] != c ) 
	        	std::reverse( face_vert_ids.begin(), face_vert_ids.end() );
	      
	      	// now copy them to the global array
	      	face_data.emplace_back( num_face_verts );
	      	for ( auto v : face_vert_ids )
	        	face_data.emplace_back( v );
	    }

	    
	    // set the cell vertices
	    temp.uGrid->InsertNextCell(
	      VTK_POLYHEDRON, num_cell_verts, vert_ids.data(),
	      num_cell_faces, face_data.data()
	    );
	}

    temp.pushPointsToGrid();



    //--------------------------------------------------------------------------
    // Write Fields
    //--------------------------------------------------------------------------

    static int count = 0;
  	for (int i=0; i<varname.size(); ++i)
    {
		int strLength = varname[i].length();
		if (varname[i][strLength-2] == '_')
		{
			if (varname[i][strLength-1] == '0')
				if (varname[i+1][strLength-1] == '1')
					if (varname[i+2][strLength-1] == '2')
					{
						temp.addVectorData(varname[i].c_str(), m.num_cells(), 1, &var_vec[i][0], &var_vec[i+1][0], &var_vec[i+2][0]);
						i = i+2;
						continue;
					}
		}
		temp.addScalarData(varname[i].c_str(), &var_vec[i][0], m.num_cells(), 1);
    }
    count++;



    //--------------------------------------------------------------------------
    // 
    //--------------------------------------------------------------------------

	return temp.getUGrid();
}

 



template< typename T >
inline void addScalar(T* data, std::string varname, vtkSmartPointer<vtkUnstructuredGrid> & uGrid, size_t numElements, int discretization=1)
{
	// discretization: cell based (1) or vextex based(0)
	ristra::io::vtk::setScalarData(varname, &data[0], numElements, discretization, uGrid);
}

template< typename T >
inline void addVector(std::vector< std::vector<T> > data, std::string varname, vtkSmartPointer<vtkUnstructuredGrid> & uGrid, size_t numElements, int discretization=1)
{
	// discretization: cell based (1) or vextex based(0)
	ristra::io::vtk::setVectorData(varname, data, numElements, discretization, uGrid);
}


template< typename T >
inline void addTensor(std::vector< std::vector<T> > data, std::string varname, vtkSmartPointer<vtkUnstructuredGrid> & uGrid, size_t numElements, int discretization=1)
{
	// discretization: cell based (1) or vextex based(0)
	ristra::io::vtk::setTensorData(varname, data, numElements, discretization, uGrid);
}


inline vtkSmartPointer<vtkUnstructuredGrid> createMesh(mesh_t &m)
{
	// Creates a mesh

    // mesh statistics
    // get the general statistics
    constexpr auto num_dims = mesh_t::num_dimensions;
    auto num_nodes = m.num_vertices();
    auto num_faces = num_dims==3 ? m.num_faces() : 0;
    auto num_elems = m.num_cells();
    auto num_elem_blk = 1;
    auto num_node_sets = 0;
    auto num_side_sets = 0;
    using  ex_real_t  = real_t;



    //--------------------------------------------------------------------------
    // Create structure
    //--------------------------------------------------------------------------

    ristra::io::vtk::UnstructuredGrid temp;



    //--------------------------------------------------------------------------
    // Point Coordinates
    //--------------------------------------------------------------------------

    std::vector<real_t> vertex_coord( num_nodes * num_dims );
    std::vector<int> pointIDs;
    for (auto v : m.vertices()) 
    {
    	auto & coords = v->coordinates();

    	pointIDs.push_back(v.id());

    	std::vector<float> vertex;
    	int count = 0;
      	for ( int i=0; i<num_dims; i++ )
      	{
      		vertex_coord[ v.id()*3 + i] = coords[i];
      		vertex.push_back(coords[i]);
      		count++;
      	}
      	if (num_dims == 2)
      		vertex.push_back(0.0);

      	temp.insertNextPoint(&vertex[0]);
    }

    temp.setPointIDs(pointIDs);


    
    //--------------------------------------------------------------------------
    // Face connectivity
    //-------------------------------------------------------------------------- 

	const auto & owned_cells = m.cells(flecsi::owned);
	auto num_owned_cells = owned_cells.size();
	auto num_cells = m.cells().size();
	std::vector< bool > is_ghost_cell( num_cells, true );
	for ( auto c : owned_cells ) 
		is_ghost_cell[c.id()] = false;


	for ( auto c : m.cells() ) 
	{
		if ( is_ghost_cell[c] )	// Skip ghost cells
			continue;

	    // get the vertices in this cell
	    auto cell_verts = m.vertices(c);
	    auto num_cell_verts = cell_verts.size();

	    // copy them to the vtk type
	    std::vector< vtkIdType > vert_ids(num_cell_verts);
	    std::transform( cell_verts.begin(), cell_verts.end(), vert_ids.begin(), [](auto && v) { return v.id(); } );

	    // get the faces
	    auto cell_faces = m.faces(c);
	    auto num_cell_faces = cell_faces.size();

	    // get the total number of vertices
	    auto tot_verts = std::accumulate( 
	      	cell_faces.begin(), cell_faces.end(), static_cast<size_t>(0),
	      	[&m](auto sum, auto f) { return sum + m.vertices(f).size(); }
	    );

	    // the list of faces that vtk requires contains the number of points in each
	    // face AND the point ids themselves.
	    std::vector< vtkIdType > face_data;
	    face_data.reserve( tot_verts + num_cell_faces );
	    for ( auto f : cell_faces ) 
	    {
	    	auto face_cells = m.cells(f);
	      	auto face_verts = m.vertices(f);
	      	auto num_face_verts = face_verts.size();

	      	// copy the face vert ids to the vtk type
	      	std::vector< vtkIdType > face_vert_ids( num_face_verts );
	      	std::transform( 
	        	face_verts.begin(), face_verts.end(), face_vert_ids.begin(),
	        	[](auto && v) { return v.id(); } 
	      	);
	      
	      	// check the direction of the vertices
	      	if ( face_cells[0] != c ) 
	        	std::reverse( face_vert_ids.begin(), face_vert_ids.end() );
	      
	      	// now copy them to the global array
	      	face_data.emplace_back( num_face_verts );
	      	for ( auto v : face_vert_ids )
	        	face_data.emplace_back( v );
	    }

	    
	    // set the cell vertices
	    temp.uGrid->InsertNextCell(
	      VTK_POLYHEDRON, num_cell_verts, vert_ids.data(),
	      num_cell_faces, face_data.data()
	    );
	}

    temp.pushPointsToGrid();

	return temp.getUGrid();
}


} // end of catalyst namespace
} // end of io namespace
} // end of ristra namespace

//} // end of interface
#endif //RISTRA_ENABLE_CATALYST


