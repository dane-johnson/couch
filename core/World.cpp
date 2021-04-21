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
 
  The physics world
*/
#include "World.h"

World* World::GetWorld() {
  if (!world) {
    world = new World();
  }

  return world;
}

void World::AddRigidbody(Rigidbody *rigidbody) {
  btWorld->addRigidBody(rigidbody->btBody);
}

void World::Step(float delta) {
  btWorld->stepSimulation(delta);
}

RaycastResult World::Raycast(const Vector3 &from, const Vector3 &to) {
  RaycastResult rcr;
  btVector3 btFrom = btVector3(from.x, from.y, from.z);
  btVector3 btTo = btVector3(to.x, to.y, to.z);
  btCollisionWorld::ClosestRayResultCallback rayCallback(btFrom, btTo);
  rayCallback.m_collisionFilterGroup = -1; // Everything
  btWorld->rayTest(btFrom, btTo, rayCallback);
  rcr.hit = rayCallback.hasHit();
  if (rcr.hit) {
    rcr.position = Vector3(rayCallback.m_hitPointWorld.getX(),
			   rayCallback.m_hitPointWorld.getY(),
			   rayCallback.m_hitPointWorld.getZ());
    rcr.normal = Vector3(rayCallback.m_hitNormalWorld.getX(),
			 rayCallback.m_hitNormalWorld.getY(),
			 rayCallback.m_hitNormalWorld.getZ());
    rcr.object = (Rigidbody*) rayCallback.m_collisionObject->getUserPointer();
  }
  return rcr;
}

World* World::world { new World() };

World::World() {
  // Some Java-ass code to follow
  collisionConfiguration = new btDefaultCollisionConfiguration();
  dispatcher = new btCollisionDispatcher(collisionConfiguration);
  overlappingPairCache = new btDbvtBroadphase();
  solver = new btSequentialImpulseConstraintSolver();
  btWorld = new btDiscreteDynamicsWorld(dispatcher, overlappingPairCache, solver, collisionConfiguration);
  btWorld->setGravity(btVector3(0, -10, 0));
}

World::~World() {
  delete btWorld;
  delete solver;
  delete overlappingPairCache;
  delete dispatcher;
  delete collisionConfiguration;
}
