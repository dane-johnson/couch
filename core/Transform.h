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
 
   A transform represents various aspects of 3d space.
*/
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

/**
   A Transform represents a position, rotation, and scale in 3D space.
*/
struct Transform {
  Transform();
  Transform(Vector3 position, Vector3 rotation);
  Transform(Vector3 position, Vector3 rotation, Vector3 scale);
  /**
     The position, according to the left-hand rule
  */
  Vector3 position;
  /**
     The rotation, in Euler angles
  */
  Vector3 rotation;
  /**
     Scaling along the specified axis
  */
  Vector3 scale;
  /**
     Returns a vector that is -Z, rotated by @ref rotation.
  */
  Vector3 Forward();
  /**
     Returns a vector that is +X, rotated by @ref rotation.
  */
  Vector3 Right();
  /**
     Returns a vector that is +Y, rotated by @ref rotation.
  */
  Vector3 Up();
  /**
     Returns a matrix that, when multiplied by a @ref Vector3
     gives a Vector rotated by @ref rotation
  */
  Matrix RotationMatrix();
};

#endif /* TRANSFORM_H */
