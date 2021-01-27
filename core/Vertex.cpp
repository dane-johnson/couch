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

Vertex::Vertex(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nz = 0.0f;
  this->ny = 0.0f;
  this->nz = 0.0f;
  this->u = 0.0f;
  this->v = 0.0f;
}

Vertex::Vertex(float x, float y, float z, float u, float v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nx = 0.0f;
  this->ny = 0.0f;
  this->nz = 0.0f;
  this->u = u;
  this->v = v;
}

Vertex::Vertex(float x, float y, float z,
	       float nx, float ny, float nz,
	       float u, float v) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->nx = nx;
  this->ny = ny;
  this->nz = nz;
  this->u = u;
  this->v = v;
}
