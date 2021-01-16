#include "types.h"

#include <iostream>

Vector3 operator+(const Vector3 &r, const Vector3 &l) {
  Vector3 val(0.0f);
  val.x = r.x + l.x;
  val.y = r.y + l.y;
  val.z = r.z + l.z;
  return val;
}

Vector3 operator*(const Vector3 &r, const cfloat &l) {
  Vector3 val(0.0f);
  val.x = r.x * l;
  val.y = r.y * l;
  val.z = r.z * l;
  return val;
}
