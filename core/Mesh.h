#ifndef MESH_H
#define MESH_H

#include <list>

#include "types.h"
#include "Spatial.h"
#include "Vertex.h"
#include "Index.h"
#include "Material.h"

class Mesh : public Spatial {
public:
  VertexList vertices;
  IndexList indices;
  Material *material;
  Mesh();
  ~Mesh();
  Mesh(VertexList vertices, IndexList indices);
  static Mesh FromFile(const char *filename);
  virtual bool IsDrawable() const {return true;}
  virtual void Draw();
  virtual void SetupMesh();
private:
  Id VAO, VBO, EBO;
};

typedef std::list<Mesh*> MeshList;

#endif /* MESH_H */
