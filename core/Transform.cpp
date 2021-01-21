#include "Transform.h"

Transform::Transform() {
  position = Vector3(0.0f);
  rotation = Vector3(0.0f);
  scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vector3 position, Vector3 rotation) {
  this->position = position;
  this->rotation = rotation;
  this->scale = Vector3(1.0f, 1.0f, 1.0f);
}

Transform::Transform(Vector3 position, Vector3 rotation, Vector3 scale) {
  this->position = position;
  this->rotation = rotation;
  this->scale = scale;
}


void Transform::Translate(cfloat x, cfloat y, cfloat z) {
  position = position + Vector3(x, y, z);
}


Matrix Transform::RotationMatrix() {
  Matrix mat(1.0f);
  
  mat = glm::rotate(mat, this->rotation.z, Vector3(0.0f, 0.0f, 1.0f));
  mat = glm::rotate(mat, this->rotation.y, Vector3(0.0f, 1.0f, 0.0f));
  mat = glm::rotate(mat, this->rotation.x, Vector3(1.0f, 0.0f, 0.0f));

  return mat;
}

Vector3 Transform::Forward() {
  return glm::vec3(RotationMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
}

Vector3 Transform::Up() {
  return glm::vec3(RotationMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

Vector3 Transform::Right() {
  return glm::vec3(RotationMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}
