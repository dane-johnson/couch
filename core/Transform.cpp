/*
   Dane Johnson <dane@danejohnson.org>
 
   LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   DESCRIPTION
 
   A transform represents various aspects of 3d space.
*/
#include "Transform.h"
#include <glm/gtc/matrix_transform.hpp>

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


Vector3 Transform::Forward() {
  return glm::vec3(RotationMatrix() * glm::vec4(0.0f, 0.0f, -1.0f, 1.0f));
}

Vector3 Transform::Up() {
  return glm::vec3(RotationMatrix() * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
}

Vector3 Transform::Right() {
  return glm::vec3(RotationMatrix() * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
}

Matrix Transform::RotationMatrix() {
  Matrix mat(1.0f);
  
  mat = glm::rotate(mat, this->rotation.z, Vector3(0.0f, 0.0f, 1.0f));
  mat = glm::rotate(mat, this->rotation.y, Vector3(0.0f, 1.0f, 0.0f));
  mat = glm::rotate(mat, this->rotation.x, Vector3(1.0f, 0.0f, 0.0f));

  return mat;
}
