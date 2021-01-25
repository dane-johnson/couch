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
  SphereCollisionShape(cfloat radius);
};

class BoxCollisionShape : public CollisionShape {
public:
  BoxCollisionShape(cfloat width, cfloat height, cfloat depth);
};

class CapsuleCollisionShape: public CollisionShape {
public:
  CapsuleCollisionShape(cfloat radius, cfloat height);
};

#endif /* COLLISIONSHAPE_H */
