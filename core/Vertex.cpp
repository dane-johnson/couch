#include "Vertex.h"

Vertex::Vertex() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z) {
  this->x = x;
  this->y = y;
  this->z = z;
}
