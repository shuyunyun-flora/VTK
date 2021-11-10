/*=========================================================================

  Program:   Visualization Toolkit

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkVRCamera
 * @brief   VR camera
 *
 * vtkVRCamera is a concrete implementation of the abstract class
 * vtkCamera.  vtkVRCamera interfaces to the VR rendering library.
 */

#ifndef vtkVRCamera_h
#define vtkVRCamera_h

#include "vtkOpenGLCamera.h"
#include "vtkRenderingVRModule.h" // For export macro

class vtkMatrix4x4;
class vtkVRRenderWindow;

class VTKRENDERINGVR_EXPORT vtkVRCamera : public vtkOpenGLCamera
{
public:
  vtkTypeMacro(vtkVRCamera, vtkOpenGLCamera);

  /**
   * Provides a matrix to go from absolute VR tracking coordinates
   * to device coordinates. Used for rendering devices.
   */
  virtual void GetTrackingToDCMatrix(vtkMatrix4x4*& TCDCMatrix) = 0;

  // A pose in VR includes more than just the basic camera values.
  // It includes all the properties needed to reproduce a view
  // in physical space when requested from a different physical space
  // This class stores those properties
  // As the VR code is still being rearchitected this signature
  // may change slightly through the end of 2021.
  class Pose
  {
  public:
    double Position[3];
    double PhysicalViewUp[3];
    double PhysicalViewDirection[3];
    double ViewDirection[3];
    double Translation[3];
    double Distance;
    double MotionFactor = 1.0;
  };

  // Fill in a Pose object based on the current camera and physical space
  // settings. As the VR code is still being rearchitected this signature
  // may change slightly through the end of 2021.
  void SetPoseFromCamera(Pose* pose, vtkVRRenderWindow* win);

  // Reproduce a pose using the current camera and render window. That is, try
  // to make the viewer's current view look like the original saved pose.
  // This is complicated by the fact that the viewer may now occupy a very
  // different position and orientation in the physical space than when the
  // pose was saved. This method accounts for this and adjusts the phjsical
  // space to best fit the requested pose.
  // As the VR code is still being rearchitected this signature
  // may change slightly through the end of 2021.
  void ApplyPoseToCamera(Pose* pose, vtkVRRenderWindow* win);

protected:
  vtkVRCamera() = default;
  ~vtkVRCamera() override = default;

private:
  vtkVRCamera(const vtkVRCamera&) = delete;
  void operator=(const vtkVRCamera&) = delete;
};

#endif