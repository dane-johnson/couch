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
