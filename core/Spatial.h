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
 
   A spatial is a node with a transform property, i.e. position, scale or rotation.
   They can be instanced on the scene tree as an anchor for some other nodes.
*/
#ifndef SPATIAL_H
#define SPATIAL_H

#include "types.h"
#include "Node.h"
#include "Transform.h"

/**
   Spatial nodes have a transform property. They can be subclassed or instanced
   as an anchor for their children.
 */
class Spatial : public Node {
public:
  virtual Name GetType() const;

  /**
     Gets the transform property of this spatial
     @return The transform
  */
  Transform GetTransform();
  /**
     Sets the transform property of this spatial.
     @param transform The transform property
  */
  void SetTransform(Transform transform);

  /**
     Directly translates the spatial by offset
     @param offset The offset of the transform operation
  */
  virtual void Translate(Vector3 offset);
  /**
     Rotates the Camera phi radians about the X axis
     @param phi The amount to rotate in radians
  */
  void RotateX(cfloat phi);
  /**
     Rotates the Camera phi radians about the Y axis
     @param phi The amount to rotate in radians
  */
  void RotateY(cfloat phi);
  /**
     Rotates the Camera phi radians about the Z axis
     @param phi The amount to rotate in radians
  */
  void RotateZ(cfloat phi);
  /**
     Scales the spatial by scale uniformly
     @param scale The amount to scale by.
  */
  void UniformScale(cfloat scale);
  
  virtual Spatial *Create();
  virtual Spatial *Duplicate();  
  virtual Spatial *Instance();
private:
  Transform transform;
};

#endif /* SPATIAL_H */
