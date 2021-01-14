#include "Transform.h"

Transform::Transform() {
  position = Vector3(0.0f);
  rotation = Vector3(0.0f);
}

Transform::Transform(Vector3 position, Vector3 rotation) {
  this->position = position;
  this->rotation = rotation;
}

void Transform::Translate(cfloat x, cfloat y, cfloat z) {
  position = position + Vector3(x, y, z);
}
