/**
   @file
   @author Dane Johnson <dane@danejohnson.org>
 
   @section LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   @section DESCRIPTION
   
   Meshes and their subclasses are anything that can be rendered
   on screen. They are divided into submeshes, each of which
   can have its own material properties.
*/
#ifndef MESH_H
#define MESH_H

#include <vector>

#include "types.h"
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

/**
   Mesh and its subclasses are anything that can be rendered on screen.
   A mesh is made up of submeshes, each of which can have one material
   property.
*/
class Mesh : public Spatial {
public:
  ~Mesh();

  /**
     @return The number of submeshes this mesh is made up of
  */
  int GetNumSubmeshes();
  /**
     Get the material property of a submesh
     @param submesh The index of the submesh who's material is desired
     @return The material property
  */
  Material GetMaterial(int submesh);
  /**
     Set the material property of a submesh
     @param submesh The index of the submesh to update
     @param material The desired material property
  */
  void SetMaterial(int submesh, Material material);

  /**
     Create a new mesh from a Wavefront file.
     A submesh will be generated for each material on the mesh.
     Material properties will be generated based on the .mat
     file, if present
     @param filename The name of the file containing the mesh.
     @return A new mesh prefab
  */
  static Mesh *FromFile(const char *filename);

  /**
     Draw this mesh, by calling Draw on all submeshes.
     The shader will be updated on each call to the material
     property of the submesh
     @param shader The shader program to use to draw
  */
  virtual void Draw(Shader *shader);

  virtual Mesh *Create();
  virtual Mesh *Duplicate();
  virtual Mesh *Instance();

  virtual Name GetType() const;
protected:
  SubMeshList submeshes;
  virtual void SetupMesh();
};

#endif /* MESH_H */
