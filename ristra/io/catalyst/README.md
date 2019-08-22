
Catalyst is an in situ library that allows us to view the results of a simulation as it is being 
executed. More information on Catalyst is available at: http://www.paraview.org/in-situ/


Contents of this document:
	I For users
	   1. Building flecsale with catalyst
	   2. Using catalyst
	   3. Using catalyst connected to a remote server

	II For developers
	   1. Adding Catalyst to an app


NOTE: Paraview 5.2.0 is required for this.
	OSX Build: http://www.paraview.org/files/v5.2/ParaView-5.2.0-Qt4-OpenGL2-MPI-OSX10.8-64bit.dmg
	Linux Build: http://www.paraview.org/files/v5.2/ParaView-5.2.0-Qt4-OpenGL2-MPI-Linux-64bit.tar.gz

	Src to build from: http://www.paraview.org/files/v5.2/ParaView-v5.2.0.tar.gz


You need to build catalyst with the following:

cmake ../ -DCMAKE_INSTALL_PREFIX=./install -DPARAVIEW_ENABLE_PYTHON=on -DPARAVIEW_USE_MPI=on

--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------

I. 1. Building flecsale with catalyst

	A ParaView build on the local machine is required. 
	Export the path to of the lib folder in ParaView build to LD_LIBRARY_PATH
 

	a. In ccmake, turn on USE_Catalyst

	b. ParaView_DIR will then be required. Point that directopry to a ParaView build directory

	c. configure, generate and build 


--------------------------------------------------------------------------------------------------

I. 2. Running a sim with catalyst
	
	a. Open ParaView (same version as the one that you built paraview with)
			On the file menu at the top, click: Catalyst -> Connect

		and the following message will appear in the terminal
			Accepting connection(s): computername:port

		and in the ParaView pipeline browser, you will see
			- builtin:
			- catalyst:


	b. launch the simulation with the paraview script
		./hydro_3d ../../apps/catalyst_adaptor/catalyst_scripts/hydro3d_live.py

	c. As soon as the simulation starts dumping data, ParaView will start intercepting the output 
			and if you click on the eye icon in the pipeline browser, the simulation results will 
			start appearing in ParaView.

	Note:
		Once the simulation appears in ParaView, you can use ParaView to pause the simulation


--------------------------------------------------------------------------------------------------

I. 3. Using catalyst connected to a remote server

	Since most simulations are not run on local workstations or laptops, we should be able to 
	remotely connect ParaView to a sim running on a server and visualize it.

	An example of that setup using Darwin is shown below.

	   Client:
	  	1. Start Paraview on your client
	  	2. From the top menu, Select File->Connect
	  	3. From the window, select "Add Server" and fill in the details below:
	  			Name: a-meaninful-name
	  			Server Type: Client /Server (reverse connection)
	  			Port: 11111

	  		Click: the "Configure" button

	  		Leave Startup type as: "Manual"
	  		Click: "Save"

	  	4. Choose the new entry and click "Connect"
	  			That should connect you to the remote paraview server

	  Server:
			1. Login to Darwin and request an allocation
			2. Load the required libraries and path as follows:
				source /projects/groups/vizproject/flecsale_vis/moduleLoad.sh

			3. Start paraview on that node in reverse connection mode:
				mpirun -np X /projects/groups/vizproject/flecsale_vis/paraview/ParaView-v5.2.0/build/bin//pvserver -rc -ch=host-name --server-port=11111 --use-offscreen-rendering -display :0.0

				Where:
					X = num of mpi processes
					host-name = ip address of host

				e.g.
					mpirun -np 8 /projects/groups/vizproject/flecsale_vis/paraview/ParaView-v5.2.0/build/bin//pvserver -rc -ch=130.55.121.27 --server-port=11111 --use-offscreen-rendering -display :0.0


		Note: Paraview on the client should be started before on the server!


		In another terminal window, Connect to the same node where Paraview was started and launch a 
		flescale app with the paraview catalyst script and, on your local computer, follow the steps 
		in I.2 to run catalyst.



--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------


II. 1. Adding Catalyst to an app
	
	The hydro3D app has catalyst support and is a good example to follow.

	Modifications needed to add Catalyst to an appliation:

		a. Modify the CMakeList for that app to include Catalyst
	
			e.g.
				if (USE_CATALYST)
					target_link_libraries( hydro_3d LINK_PRIVATE common catalystadaptor ${ALE_LIBRARIES} )
					vtk_mpi_link(hydro_3d)
				else()
					target_link_libraries( hydro_3d common ${ALE_LIBRARIES} )
				endif()

			Having the selection mechanism will allow users to still not build with catalyst and have a functional app. 
			An example of this is at apps/hydro/3d/CMakeLists.txt


		b. Modify the source to point to catalyst headers

			e.g. Add: 

			#ifdef USE_CATALYST
				#include "flecsaleAdaptor.h"
				#include "flecsale_unstructuredGrid.h"
			#endif

			Then Catalyst needs to be called in the intialization, for each timestep, and when finishing. 
			An example of this is at: apps/hydro/driver.h


--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------

--------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------


APPENDIX:

I. An example of module load on Darwin:
	moduleLoad.sh 
	#!/bin/bash
	module purge
	module load anaconda/Anaconda2
	module load cmake/3.7.1
	module load doxygen/1.8.10
	module load cinch/cinch-utils
	module load ngc/devel-gnu
	module unload gcc/5.2.0 
	module load openmpi/1.6.5-gcc_5.3.0

	export LD_RUN_PATH=/projects/groups/vizproject/flecsale_vis/paraview/dependencies/mesa-12.0.3/install/lib:$LD_RUN_PATH
	export LD_LIBRARY_PATH=/projects/groups/vizproject/flecsale_vis/paraview/dependencies/llvm-3.8.1.src/install/lib/:$LD_LIBRARY_PATH
	export LD_LIBRARY_PATH=/projects/groups/vizproject/flecsale_vis/paraview/ParaView-v5.2.0/build/lib/:$LD_LIBRARY_PATH


Example build: /projects/groups/vizproject/flecsale_vis/ on Darwin


Cereal is available at: /projects/groups/vizproject/flecsale_vis/cereal
ParaView 5.2 is available at: /projects/groups/vizproject/flecsale_vis/paraview/ParaView-v5.2.0/

More info on catalyst is available at: http://www.paraview.org/files/v5.2/ParaViewCatalystGuide-5.2.0.pdf
