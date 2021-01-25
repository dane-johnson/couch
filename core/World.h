#ifndef WORLD_H
#define WORLD_H

#include <btBulletDynamicsCommon.h>

#include "Rigidbody.h"

class World {
public:
  static World* GetWorld();
  void AddRigidbody(Rigidbody *rigidbody);
  void Step(cfloat delta);
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
