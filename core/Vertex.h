#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "types.h"

struct Vertex {
  Vertex();
  Vertex(cfloat x, cfloat y, cfloat z);
  Vertex(cfloat x, cfloat y, cfloat z, cfloat u, cfloat v);
  Vertex(cfloat x, cfloat y, cfloat z,
	 cfloat nx, float ny, cfloat nz,
	 cfloat u, cfloat v);
  cfloat x, y, z;
  cfloat nx, ny, nz;
  cfloat u, v;
};

typedef std::vector<Vertex> VertexList;

#endif /* VERTEX_H */
