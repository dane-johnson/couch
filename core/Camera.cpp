/*
   Dane Johnson <dane@danejohnson.org>
 
   LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   DESCRIPTION
 
   This file defines the cameras that can be used to render the scene
*/
#include "Camera.h"

Camera::Camera() {
  if (!currentCamera) {
    currentCamera = this;
  }
}

void Camera::MakeCurrent() {
  currentCamera = this;
}

Camera*Camera::GetCurrentCamera() {
  return currentCamera;
}

Camera *Camera::currentCamera = nullptr;
