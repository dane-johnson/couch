#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

struct Transform {
  Transform();
  Transform(Vector3 position, Vector3 rotation);
  Vector3 position;
  Vector3 rotation;
  void Translate(cfloat x, cfloat y, cfloat z);
};

#endif /* TRANSFORM_H */
