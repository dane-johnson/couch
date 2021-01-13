#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "types.h"

struct Vertex {
  Vertex();
  Vertex(cfloat x, cfloat y, cfloat z);
  cfloat x, y, z;
};

typedef std::vector<Vertex> VertexList;

#endif /* VERTEX_H */
