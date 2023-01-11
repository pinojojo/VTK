#!/usr/bin/env python
from vtkmodules.vtkFiltersCore import vtkFlyingEdges2D
from vtkmodules.vtkFiltersModeling import vtkOutlineFilter
from vtkmodules.vtkIOImage import vtkPNGReader
from vtkmodules.vtkRenderingCore import (
    vtkActor,
    vtkPolyDataMapper,
    vtkRenderWindow,
    vtkRenderWindowInteractor,
    vtkRenderer,
)
import vtkmodules.vtkInteractionStyle
import vtkmodules.vtkRenderingFreeType
import vtkmodules.vtkRenderingOpenGL2
from vtkmodules.util.misc import vtkGetDataRoot
VTK_DATA_ROOT = vtkGetDataRoot()

# Create the RenderWindow, Renderer and both Actors
#
ren1 = vtkRenderer()
renWin = vtkRenderWindow()
renWin.SetMultiSamples(0)
renWin.AddRenderer(ren1)
iren = vtkRenderWindowInteractor()
iren.SetRenderWindow(renWin)

# Pipeline
reader = vtkPNGReader()
reader.SetFileName("" + str(VTK_DATA_ROOT) + "/Data/fullhead15.png")
reader.Update()
scalarRange = reader.GetOutput().GetPointData().GetScalars().GetRange()

iso = vtkFlyingEdges2D()
iso.SetInputConnection(reader.GetOutputPort())
iso.GenerateValues(12,scalarRange)

isoMapper = vtkPolyDataMapper()
isoMapper.SetInputConnection(iso.GetOutputPort())
isoMapper.SetScalarRange(scalarRange)

isoActor = vtkActor()
isoActor.SetMapper(isoMapper)
isoActor.GetProperty().SetColor(1,1,1)

outline = vtkOutlineFilter()
outline.SetInputConnection(reader.GetOutputPort())

outlineMapper = vtkPolyDataMapper()
outlineMapper.SetInputConnection(outline.GetOutputPort())

outlineActor = vtkActor()
outlineActor.SetMapper(outlineMapper)

# Add the actors to the renderer, set the background and size
#
ren1.AddActor(outlineActor)
ren1.AddActor(isoActor)
ren1.SetBackground(0,0,0)
renWin.SetSize(300,300)
ren1.ResetCamera()
iren.Initialize()

renWin.Render()
iren.Start()
# --- end of script --
