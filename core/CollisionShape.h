#ifndef COLLISIONSHAPE_H
#define COLLISIONSHAPE_H

#include <btBulletDynamicsCommon.h>

#include "types.h"

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
  SphereCollisionShape(float radius);
};

class BoxCollisionShape : public CollisionShape {
public:
  BoxCollisionShape(float width, float height, float depth);
};

class CapsuleCollisionShape: public CollisionShape {
public:
  CapsuleCollisionShape(float radius, float height);
};

#endif /* COLLISIONSHAPE_H */
