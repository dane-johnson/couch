#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <btBulletDynamicsCommon.h>

#include "types.h"
#include "Spatial.h"
#include "CollisionShape.h"

class Rigidbody : public Spatial {
public:
  Rigidbody();
  virtual Rigidbody *Create();
  virtual Rigidbody *Duplicate();
  virtual Rigidbody *Instance();
  
  void SetCollisionShape(CollisionShape collisionShape);
  cfloat mass = 1.0f;

  void ApplyImpulse(Vector3 impulse);
  void ApplyForce(Vector3 force);

  void SetCharacter(bool character);
private:
  bool character = false;
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
