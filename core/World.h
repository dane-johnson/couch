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
 
   The physics world
*/
#ifndef WORLD_H
#define WORLD_H

#include <btBulletDynamicsCommon.h>

#include "Rigidbody.h"

/**
   World is the object that performs the rigidbody physics simulation. Presently there is only one world.
*/
class World {
public:
  /**
     @returns the World singleton
  */
  static World* GetWorld();
  /**
     Add a rigidbody to the physics simulation
     @param rigidbody the rigidbody to add
  */
  void AddRigidbody(Rigidbody *rigidbody);
  /**
     Advance the physics simulation
     @param delta the time that has passed since the last physics update
  */
  void Step(float delta);
private:
  static World* world;
  btDiscreteDynamicsWorld *btWorld;
  btDefaultCollisionConfiguration *collisionConfiguration;
  btCollisionDispatcher *dispatcher;
  btBroadphaseInterface *overlappingPairCache;
  btSequentialImpulseConstraintSolver *solver;
  World();
  ~World();
};

#endif /* WORLD_H */
