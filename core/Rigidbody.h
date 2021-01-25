#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <btBulletDynamicsCommon.h>

#include "types.h"
#include "Spatial.h"

class Rigidbody : public Spatial {
public:
  Rigidbody();
  virtual Rigidbody *Create();
  virtual Rigidbody *Duplicate();
  virtual Rigidbody *Instance();
  cfloat mass = 1.0f;
private:
  btRigidBody *btBody;
  btCollisionShape *collisionShape;
  friend class World;
};

class RigidbodyMotionState : public btMotionState {
public:
  RigidbodyMotionState(Rigidbody *rigidbody);
  virtual void getWorldTransform(btTransform &worldTrans) const;
  virtual void setWorldTransform(const btTransform &worldTrans);
private:
  Rigidbody *rigidbody;
};

#endif /* RIGIDBODY_H */
