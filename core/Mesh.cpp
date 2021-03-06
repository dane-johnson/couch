/*
  Dane Johnson <dane@danejohnson.org>
 
  LICENSE
 
  Couch  Copyright (C) 2021 Dane Johnson

  This program comes with ABSOLUTELY NO WARRANTY; without event the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for details at
  https://www.gnu.org/licenses/gpl-3.0.html
  
  This is free software, and you are welcome to redistribute it
  under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.
 
  DESCRIPTION
   
  Meshes and their subclasses are anything that can be rendered
  on screen. They are divided into submeshes, each of which
  can have its own material properties.
*/
#include "Mesh.h"

// Thirdparty includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


SubMesh *aiMesh2SubMesh(aiMesh *mesh);
Color aiColor3D2Color(aiColor3D aicolor);


SubMesh::SubMesh() {}

SubMesh::SubMesh(VertexList vertices, IndexList indices) {
  this->vertices = vertices;
  this->indices = indices;
}

void SubMesh::SetupSubMesh() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
	       &vertices[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(Index),
	       &indices[0], GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
  // Vertex normal
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (3 * sizeof(float)));
  // Vertex UV
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (6 * sizeof(float)));

  glBindVertexArray(0);
}

void SubMesh::Draw(Shader *shader) {
  shader->UpdateMaterial(material);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

SubMesh *SubMesh::Duplicate() {
  SubMesh* submesh = new SubMesh();
  
  submesh->VAO = VAO;
  submesh->indices = indices;
  submesh->material = material;

  return submesh;
}

Mesh::~Mesh() {
  for (SubMesh *sub : submeshes) {
    delete sub;
  }
}

int Mesh::GetNumSubmeshes() {
  return submeshes.size();
}

Material Mesh::GetMaterial(int submesh) {
  if (submesh >= GetNumSubmeshes()) {
    throw "Submesh index out of range";
  }
  return submeshes[submesh]->material;
}

void Mesh::SetMaterial(int submesh, Material material) {
  if (submesh >= GetNumSubmeshes()) {
    Util::Die("Submesh index out of range");
  }
  submeshes[submesh]->material = material;
}

Mesh* Mesh::FromFile(const char *filename) {
  // HOCUS: https://assimp-docs.readthedocs.io/en/latest/usage/use_the_lib.html
  Assimp::Importer importer;

  const aiScene* scene = importer.ReadFile(
    filename, // Read the file
    aiProcess_Triangulate | // We only do triangles
    aiProcess_GenNormals | // We want normals precalculated
    aiProcess_GenUVCoords // We want UV mappings precalculated
    );

  if (!scene) {
    Util::Die(importer.GetErrorString());
  }

  aiNode *root = scene->mRootNode;
  if (root->mNumChildren == 1) {
    root = root->mChildren[0];
  }
  Mesh *my_mesh = new Mesh();
  for (int i = 0; i < root->mNumMeshes; i++) {
    aiMesh *mesh_to_import = scene->mMeshes[root->mMeshes[i]];
    my_mesh->submeshes.push_back(aiMesh2SubMesh(mesh_to_import));
  }

  my_mesh->SetupMesh();

  return my_mesh;
}

void Mesh::Draw(Shader *shader) {
  for (SubMesh *sub : submeshes) {
    sub->Draw(shader);
  }
}

Mesh *Mesh::Create() {
  return new Mesh;
}

Mesh *Mesh::Duplicate() {
  Mesh *mesh = static_cast<Mesh*>(Spatial::Duplicate());
  // Duplicate submeshes
  mesh->submeshes = SubMeshList();

  for (SubMesh *submesh : submeshes) {
    mesh->submeshes.push_back(submesh->Duplicate());
  }

  return mesh;
}

Mesh *Mesh::Instance() {
  return static_cast<Mesh*>(Node::Instance());
}

Name Mesh::GetType() const {return "Mesh";}

void Mesh::SetupMesh() {
  for (SubMesh *sub : submeshes) {
    sub->SetupSubMesh();
  }
}


SubMesh *aiMesh2SubMesh(aiMesh *aimesh){
  SubMesh *sub = new SubMesh();
  for (int i = 0; i < aimesh->mNumVertices; i++) {
    aiVector3D aiPosition = aimesh->mVertices[i];
    aiVector3D aiNormal = aimesh->mNormals[i];
    aiVector3D aiUV = aimesh->mTextureCoords[0][i]; // TODO get ALL texture coords
    Vertex vertex(aiPosition.x, aiPosition.y, aiPosition.z,
		  aiNormal.x, aiNormal.y, aiNormal.z,
		  aiUV.x, aiUV.y);
    sub->vertices.push_back(vertex);
  }
  for (int i = 0; i < aimesh->mNumFaces; i++) {
    // We're importing triangulated meshes, so each face is three indices
    unsigned int *face = aimesh->mFaces[i].mIndices;
    Index index(face[0], face[1], face[2]);
    sub->indices.push_back(index);
  }
  
  return sub;
}

Color aiColor3D2Color(aiColor3D aicolor) {
  Color color;
  color.r = aicolor.r;
  color.g = aicolor.g;
  color.b = aicolor.b;
  return color;
}
