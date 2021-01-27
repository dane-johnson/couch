#ifndef VERTEX_H
#define VERTEX_H

#include <vector>

#include "types.h"

struct Vertex {
  Vertex();
  Vertex(float x, float y, float z);
  Vertex(float x, float y, float z, float u, float v);
  Vertex(float x, float y, float z,
	 float nx, float ny, float nz,
	 float u, float v);
  float x, y, z;
  float nx, ny, nz;
  float u, v;
};

typedef std::vector<Vertex> VertexList;

#endif /* VERTEX_H */
