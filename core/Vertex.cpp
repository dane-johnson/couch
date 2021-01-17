#include "Vertex.h"

Vertex::Vertex() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  u = 0.0f;
  v = 0.0f;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->u = 0.0f;
  this->v = 0.0f;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z, cfloat u, cfloat v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->u = u;
  this->v = v;
}
