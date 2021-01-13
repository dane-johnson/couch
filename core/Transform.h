#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "types.h"

struct Transform {
  Transform();
  Transform(Vector3 position);
  Vector3 position;
};

#endif /* TRANSFORM_H */
