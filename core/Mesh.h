#ifndef MESH_H
#define MESH_H

#include <list>
#include <vector>

// Thirdparty includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "types.h"
#include "Util.h"
#include "Spatial.h"
#include "Vertex.h"
#include "Index.h"
#include "Material.h"

#include "Shaders/Shader.h"

class SubMesh {
public:
  SubMesh();
  SubMesh(VertexList vertices, IndexList indices);
  VertexList vertices;
  IndexList indices;
  Material *material;
  void SetupSubMesh();
  void Draw(Shader *shader);
private:
  Id VAO, VBO, EBO;
};

typedef std::vector<SubMesh*> SubMeshList;

class Mesh : public Spatial {
public:
  Mesh();
  ~Mesh();
  void SetMaterial(int submesh, Material *material);
  static Mesh *FromFile(const char *filename);
  virtual bool IsDrawable() const {return true;}
  virtual void Draw(Shader *shader);
  virtual void SetupMesh();
protected:
  SubMeshList submeshes;
private:
  static SubMesh *aiMesh2SubMesh(aiMesh *mesh);
};

typedef std::list<Mesh*> MeshList;

#endif /* MESH_H */
