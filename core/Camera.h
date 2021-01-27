/**
   @file
   @author Dane Johnson <dane@danejohnson.org>
 
   @section LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   @section DESCRIPTION
 
   This file defines the cameras that can be used to render the scene
*/
#ifndef CAMERA_H
#define CAMERA_H

#include "Spatial.h"

/**
   The common 3D camera
 */
class Camera : public Spatial {
public:
  Camera();
  /**
     Sets this camera as the one that Couch will use to render
  */
  void MakeCurrent();
  /**
     Get the Camera that couch is using to render
     @return The camera
  */
  static Camera *GetCurrentCamera();
private:
  static Camera *currentCamera;
};

#endif /* CAMERA_H */
