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
 
   Defines various collision shapes for rigidbodies and trigger areas
*/
#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include <btBulletDynamicsCommon.h>

#include "types.h"
#include "Mesh.h"

/**
   Base collision shape, should not be instanced directly
*/
class CollisionShape {
public:
  CollisionShape();
protected:
  btCollisionShape *shape;
private:
  friend class Rigidbody;
};

class SphereCollisionShape : public CollisionShape {
public:
  /**
     Creates a collision sphere with a defined radius
     @param radius The radius
  */
  SphereCollisionShape(float radius);
};

class BoxCollisionShape : public CollisionShape {
public:
  /**
     Creates a collision cube with the desired width, height, and depth
     @param width The desired width
     @param height The desired height
     @param depth The desired depth
  */
  BoxCollisionShape(float width, float height, float depth);
};

class CapsuleCollisionShape: public CollisionShape {
public:
  /**
     Creates a collision shape that is a cylinder with height, capped with a hemisphere of radius
     @param radius The hemisphere radius
     @param height The cylinder height
  */
  CapsuleCollisionShape(float radius, float height);
};

class MeshCollisionShape: public CollisionShape {
public:
  /**
     Creates a concave mesh with the same faces as mesh
     @param mesh The mesh who's faces to use
  */
  MeshCollisionShape(Mesh *mesh);
};

#endif /* COLLISIONSHAPE_H */
