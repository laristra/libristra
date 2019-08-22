
from paraview.simple import *
from paraview import coprocessing


#--------------------------------------------------------------
# Code generated from cpstate.py to create the CoProcessor.
# ParaView 5.2.0 64 bits


# ----------------------- CoProcessor definition -----------------------

def CreateCoProcessor():
  def _CreatePipeline(coprocessor, datadescription):
    class Pipeline:
      # state file generated using paraview version 5.2.0

      # ----------------------------------------------------------------
      # setup views used in the visualization
      # ----------------------------------------------------------------

      #### disable automatic camera reset on 'Show'
      paraview.simple._DisableFirstRenderCameraReset()

      # Create a new 'Render View'
      renderView1 = CreateView('RenderView')
      renderView1.ViewSize = [2880, 1736]
      renderView1.AxesGrid = 'GridAxes3DActor'
      renderView1.CenterOfRotation = [0.6, 0.6, 0.6]
      renderView1.StereoType = 0
      renderView1.CameraPosition = [-1.1770166413041572, -1.908973891099763, -1.9825803683536123]
      renderView1.CameraFocalPoint = [0.5999999999999998, 0.5999999999999998, 0.6000000000000003]
      renderView1.CameraViewUp = [-0.8499326689726643, 0.5209827260414173, 0.07868581434704111]
      renderView1.CameraParallelScale = 1.0392304845413265
      renderView1.Background = [0.0, 0.0, 0.0]

      # register the view with coprocessor
      # and provide it with information such as the filename to use,
      # how frequently to write the images, etc.
      coprocessor.RegisterView(renderView1,
          filename='image_%t.png', freq=1, fittoscreen=0, magnification=1, width=2880, height=1736, cinema={"composite":True, "floatValues":True, "camera":"phi-theta", "phi":[-180,-150,-120,-90,-60,-30,0,30,60,90,120,150],"theta":[-90,-64,-38,-12,13,38,63,88], "roll":[1], "initial":{ "eye": [-1.17702,-1.90897,-1.98258], "at": [0.6,0.6,0.6], "up": [-0.849933,0.520983,0.0786858] }, "tracking":{ "object":"None" } })
      renderView1.ViewTime = datadescription.GetTime()

      # ----------------------------------------------------------------
      # setup the data processing pipelines
      # ----------------------------------------------------------------

      # create a new 'Legacy VTK Reader'
      # create a producer from a simulation input
      sedov_3d0000000vtk = coprocessor.CreateProducer(datadescription, 'input')

      # create a new 'Parallel UnstructuredGrid Writer'
      parallelUnstructuredGridWriter1 = servermanager.writers.XMLPUnstructuredGridWriter(Input=sedov_3d0000000vtk)

      # register the writer with coprocessor
      # and provide it with information such as the filename to use,
      # how frequently to write the data, etc.
      coprocessor.RegisterWriter(parallelUnstructuredGridWriter1, filename='sedov_3d000000%t.vtk', freq=1)

      # ----------------------------------------------------------------
      # setup color maps and opacity mapes used in the visualization
      # note: the Get..() functions create a new object, if needed
      # ----------------------------------------------------------------

      # get color transfer function/color map for 'cell_density'
      cell_densityLUT = GetColorTransferFunction('cell_density')
      cell_densityLUT.RGBPoints = [1.0, 0.231373, 0.298039, 0.752941, 1.00390625, 0.865003, 0.865003, 0.865003, 1.0078125, 0.705882, 0.0156863, 0.14902]
      cell_densityLUT.ScalarRangeInitialized = 1.0

      # get opacity transfer function/opacity map for 'cell_density'
      cell_densityPWF = GetOpacityTransferFunction('cell_density')
      cell_densityPWF.Points = [1.0, 0.0, 0.5, 0.0, 1.0078125, 1.0, 0.5, 0.0]
      cell_densityPWF.ScalarRangeInitialized = 1

      # ----------------------------------------------------------------
      # setup the visualization in view 'renderView1'
      # ----------------------------------------------------------------

      # show data from sedov_3d0000000vtk
      sedov_3d0000000vtkDisplay = Show(sedov_3d0000000vtk, renderView1)
      # trace defaults for the display properties.
      sedov_3d0000000vtkDisplay.Representation = 'Surface With Edges'
      sedov_3d0000000vtkDisplay.ColorArrayName = ['CELLS', 'cell_density']
      sedov_3d0000000vtkDisplay.LookupTable = cell_densityLUT
      sedov_3d0000000vtkDisplay.OSPRayScaleArray = 'node_velocity'
      sedov_3d0000000vtkDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
      sedov_3d0000000vtkDisplay.SelectOrientationVectors = 'None'
      sedov_3d0000000vtkDisplay.ScaleFactor = 0.12
      sedov_3d0000000vtkDisplay.SelectScaleArray = 'None'
      sedov_3d0000000vtkDisplay.GlyphType = 'Arrow'
      sedov_3d0000000vtkDisplay.ScalarOpacityUnitDistance = 0.10392304845413267
      sedov_3d0000000vtkDisplay.GaussianRadius = 0.06
      sedov_3d0000000vtkDisplay.SetScaleArray = [None, '']
      sedov_3d0000000vtkDisplay.ScaleTransferFunction = 'PiecewiseFunction'
      sedov_3d0000000vtkDisplay.OpacityArray = [None, '']
      sedov_3d0000000vtkDisplay.OpacityTransferFunction = 'PiecewiseFunction'

      # show color legend
      sedov_3d0000000vtkDisplay.SetScalarBarVisibility(renderView1, True)

      # setup the color legend parameters for each legend in this view

      # get color legend/bar for cell_densityLUT in view renderView1
      cell_densityLUTColorBar = GetScalarBar(cell_densityLUT, renderView1)
      cell_densityLUTColorBar.Title = 'cell_density'
      cell_densityLUTColorBar.ComponentTitle = ''

      # ----------------------------------------------------------------
      # finally, restore active source
      SetActiveSource(parallelUnstructuredGridWriter1)
      # ----------------------------------------------------------------
    return Pipeline()

  class CoProcessor(coprocessing.CoProcessor):
    def CreatePipeline(self, datadescription):
      self.Pipeline = _CreatePipeline(self, datadescription)

  coprocessor = CoProcessor()
  # these are the frequencies at which the coprocessor updates.
  freqs = {'input': [1, 1]}
  coprocessor.SetUpdateFrequencies(freqs)
  return coprocessor

#--------------------------------------------------------------
# Global variables that will hold the pipeline for each timestep
# Creating the CoProcessor object, doesn't actually create the ParaView pipeline.
# It will be automatically setup when coprocessor.UpdateProducers() is called the
# first time.
coprocessor = CreateCoProcessor()

#--------------------------------------------------------------
# Enable Live-Visualizaton with ParaView
coprocessor.EnableLiveVisualization(False, 1)


# ---------------------- Data Selection method ----------------------

def RequestDataDescription(datadescription):
    "Callback to populate the request for current timestep"
    global coprocessor
    if datadescription.GetForceOutput() == True:
        # We are just going to request all fields and meshes from the simulation
        # code/adaptor.
        for i in range(datadescription.GetNumberOfInputDescriptions()):
            datadescription.GetInputDescription(i).AllFieldsOn()
            datadescription.GetInputDescription(i).GenerateMeshOn()
        return

    # setup requests for all inputs based on the requirements of the
    # pipeline.
    coprocessor.LoadRequestedData(datadescription)

# ------------------------ Processing method ------------------------

def DoCoProcessing(datadescription):
    "Callback to do co-processing for current timestep"
    global coprocessor

    # Update the coprocessor by providing it the newly generated simulation data.
    # If the pipeline hasn't been setup yet, this will setup the pipeline.
    coprocessor.UpdateProducers(datadescription)

    # Write output data, if appropriate.
    coprocessor.WriteData(datadescription);

    # Write image capture (Last arg: rescale lookup table), if appropriate.
    coprocessor.WriteImages(datadescription, rescale_lookuptable=False)

    # Live Visualization, if enabled.
    coprocessor.DoLiveVisualization(datadescription, "localhost", 22222)
