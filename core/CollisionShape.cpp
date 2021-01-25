#include "CollisionShape.h"

CollisionShape::CollisionShape() {
  shape = nullptr;
}

SphereCollisionShape::SphereCollisionShape(cfloat radius) {
  shape = new btSphereShape(radius);
}

BoxCollisionShape::BoxCollisionShape(cfloat width, cfloat height, cfloat depth) {
  shape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
}

CapsuleCollisionShape::CapsuleCollisionShape(cfloat radius, cfloat height) {
  shape = new btCapsuleShape(radius, height);
}
