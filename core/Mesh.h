#ifndef MESH_H
#define MESH_H

#include <list>

#include "types.h"
#include "Spatial.h"
#include "Drawable.h"
#include "Vertex.h"
#include "Index.h"

class Mesh : public Spatial, public Drawable {
public:
  VertexList vertices;
  IndexList indices;
  Mesh();
  ~Mesh();
  Mesh(VertexList vertices, IndexList indices);
  virtual void Draw();
  virtual void SetupMesh();
private:
  Id VAO, VBO, EBO;
};

typedef std::list<Mesh*> MeshList;

#endif /* MESH_H */
