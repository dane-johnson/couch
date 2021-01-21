#include "Vertex.h"

Vertex::Vertex() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
  nx = 0.0f;
  ny = 0.0f;
  nz = 0.0f;
  u = 0.0f;
  v = 0.0f;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nz = 0.0f;
  this->ny = 0.0f;
  this->nz = 0.0f;
  this->u = 0.0f;
  this->v = 0.0f;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z, cfloat u, cfloat v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nx = 0.0f;
  this->ny = 0.0f;
  this->nz = 0.0f;
  this->u = u;
  this->v = v;
}

Vertex::Vertex(cfloat x, cfloat y, cfloat z,
	       cfloat nx, float ny, cfloat nz,
	       cfloat u, cfloat v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nx = nx;
  this->ny = ny;
  this->nz = nz;
  this->u = u;
  this->v = v;
}
