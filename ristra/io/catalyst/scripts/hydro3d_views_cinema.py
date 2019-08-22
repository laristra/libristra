
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
      renderView1.StereoType = 0
      renderView1.CameraPosition = [-1.6648535514349747, -2.039753678314231, -2.0649019363603025]
      renderView1.CameraViewUp = [-0.8039807283835076, 0.5911747533508945, 0.06424483939145169]
      renderView1.CameraParallelScale = 0.8660254037844386
      renderView1.Background = [0.0, 0.0, 0.0]

      # register the view with coprocessor
      # and provide it with information such as the filename to use,
      # how frequently to write the images, etc.
      coprocessor.RegisterView(renderView1,
          filename='image_%t.png', freq=1, fittoscreen=0, magnification=1, width=2880, height=1736, cinema={"composite":True, "floatValues":True, "camera":"phi-theta", "phi":[-180,-150,-120,-90,-60,-30,0,30,60,90,120,150],"theta":[-90,-64,-38,-12,13,38,63,88], "roll":[1], "initial":{ "eye": [-1.66485,-2.03975,-2.0649], "at": [0,0,0], "up": [-0.803981,0.591175,0.0642448] }, "tracking":{ "object":"None" } })
      renderView1.ViewTime = datadescription.GetTime()

      # ----------------------------------------------------------------
      # setup the data processing pipelines
      # ----------------------------------------------------------------

      # create a new 'Legacy VTK Reader'
      # create a producer from a simulation input
      shock_box_3d0000048vtk = coprocessor.CreateProducer(datadescription, 'input')

      # create a new 'Parallel UnstructuredGrid Writer'
      parallelUnstructuredGridWriter1 = servermanager.writers.XMLPUnstructuredGridWriter(Input=shock_box_3d0000048vtk)

      # register the writer with coprocessor
      # and provide it with information such as the filename to use,
      # how frequently to write the data, etc.
      coprocessor.RegisterWriter(parallelUnstructuredGridWriter1, filename='shock_box_3d00000%t.vtk', freq=1)

      # ----------------------------------------------------------------
      # setup color maps and opacity mapes used in the visualization
      # note: the Get..() functions create a new object, if needed
      # ----------------------------------------------------------------

      # get color transfer function/color map for 'density'
      densityLUT = GetColorTransferFunction('density')
      densityLUT.RGBPoints = [0.12634281439212472, 0.231373, 0.298039, 0.752941, 0.5631714071960624, 0.865003, 0.865003, 0.865003, 1.0, 0.705882, 0.0156863, 0.14902]
      densityLUT.ScalarRangeInitialized = 1.0

      # get opacity transfer function/opacity map for 'density'
      densityPWF = GetOpacityTransferFunction('density')
      densityPWF.Points = [0.12634281439212472, 0.0, 0.5, 0.0, 1.0, 1.0, 0.5, 0.0]
      densityPWF.ScalarRangeInitialized = 1

      # ----------------------------------------------------------------
      # setup the visualization in view 'renderView1'
      # ----------------------------------------------------------------

      # show data from shock_box_3d0000048vtk
      shock_box_3d0000048vtkDisplay = Show(shock_box_3d0000048vtk, renderView1)
      # trace defaults for the display properties.
      shock_box_3d0000048vtkDisplay.Representation = 'Surface With Edges'
      shock_box_3d0000048vtkDisplay.ColorArrayName = ['CELLS', 'density']
      shock_box_3d0000048vtkDisplay.LookupTable = densityLUT
      shock_box_3d0000048vtkDisplay.OSPRayScaleArray = 'density'
      shock_box_3d0000048vtkDisplay.OSPRayScaleFunction = 'PiecewiseFunction'
      shock_box_3d0000048vtkDisplay.SelectOrientationVectors = 'None'
      shock_box_3d0000048vtkDisplay.ScaleFactor = 0.1
      shock_box_3d0000048vtkDisplay.SelectScaleArray = 'None'
      shock_box_3d0000048vtkDisplay.GlyphType = 'Arrow'
      shock_box_3d0000048vtkDisplay.ScalarOpacityUnitDistance = 0.04330127018922194
      shock_box_3d0000048vtkDisplay.GaussianRadius = 0.05
      shock_box_3d0000048vtkDisplay.SetScaleArray = [None, '']
      shock_box_3d0000048vtkDisplay.ScaleTransferFunction = 'PiecewiseFunction'
      shock_box_3d0000048vtkDisplay.OpacityArray = [None, '']
      shock_box_3d0000048vtkDisplay.OpacityTransferFunction = 'PiecewiseFunction'

      # show color legend
      shock_box_3d0000048vtkDisplay.SetScalarBarVisibility(renderView1, True)

      # setup the color legend parameters for each legend in this view

      # get color legend/bar for densityLUT in view renderView1
      densityLUTColorBar = GetScalarBar(densityLUT, renderView1)
      densityLUTColorBar.Title = 'density'
      densityLUTColorBar.ComponentTitle = ''

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
