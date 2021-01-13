#ifndef MESH_H
#define MESH_H

#include <list>

#include "types.h"
#include "Vertex.h"
#include "Index.h"
#include "Transform.h"

class Mesh {
public:
  VertexList vertices;
  IndexList indices;
  Transform transform;
  Mesh();
  Mesh(VertexList vertices, IndexList indices);
  void Draw();
  virtual void SetupMesh();
private:
  Id VAO, VBO, EBO;
};

typedef std::list<Mesh*> MeshList;

#endif /* MESH_H */
