#include "CollisionShape.h"

CollisionShape::CollisionShape() {
  shape = nullptr;
}

SphereCollisionShape::SphereCollisionShape(float radius) {
  shape = new btSphereShape(radius);
}

BoxCollisionShape::BoxCollisionShape(float width, float height, float depth) {
  shape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
}

CapsuleCollisionShape::CapsuleCollisionShape(float radius, float height) {
  shape = new btCapsuleShape(radius, height);
}
