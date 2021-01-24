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
  Material material;
  void Draw(Shader *shader);
  SubMesh *Duplicate();
private:
  Id VAO, VBO, EBO;
  void SetupSubMesh();
  friend class Mesh;  
};

typedef std::vector<SubMesh*> SubMeshList;

class Mesh : public Spatial {
public:
  Mesh();
  ~Mesh();
  Material GetMaterial(int submesh);
  void SetMaterial(int submesh, Material material);
  static Mesh *FromFile(const char *filename);
  virtual bool IsDrawable() const {return true;}
  virtual void Draw(Shader *shader);
  virtual Name GetType() const;
  virtual Mesh *Create();
  virtual Mesh *Duplicate();
  virtual Mesh *Instance();
protected:
  SubMeshList submeshes;
  virtual void SetupMesh();
private:
  static SubMesh *aiMesh2SubMesh(aiMesh *mesh, aiMaterial *material);
  static Color aiColor3D2Color(aiColor3D aicolor);
};

typedef std::list<Mesh*> MeshList;

#endif /* MESH_H */
