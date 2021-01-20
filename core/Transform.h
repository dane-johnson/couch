#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

struct Transform {
  Transform();
  Transform(Vector3 position, Vector3 rotation);
  Transform(Vector3 position, Vector3 rotation, Vector3 scale);
  Vector3 position;
  Vector3 rotation;
  Vector3 scale;
  void Translate(cfloat x, cfloat y, cfloat z);
  Vector3 Forward();
};

#endif /* TRANSFORM_H */
