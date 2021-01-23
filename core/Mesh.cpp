#include "Mesh.h"

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

Name Mesh::GetType() const {return "Mesh";}

Mesh::Mesh() {}

Mesh::~Mesh() {
  for (SubMesh *sub : submeshes) {
    delete sub;
  }
}

Mesh *Mesh::Duplicate() {
  Mesh *dup = new Mesh(*this);
  return dup;
}

void Mesh::SetupMesh() {
  for (SubMesh *sub : submeshes) {
    sub->SetupSubMesh();
  }
}

Material Mesh::GetMaterial(int submesh) {
  return submeshes[submesh]->material;
}

void Mesh::SetMaterial(int submesh, Material material) {
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
    my_mesh->submeshes.push_back(aiMesh2SubMesh(mesh_to_import, scene->mMaterials[mesh_to_import->mMaterialIndex]));
  }

  my_mesh->SetupMesh();

  return my_mesh;
}

SubMesh *Mesh::aiMesh2SubMesh(aiMesh *aimesh, aiMaterial* material){
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

  // Get material properties
  aiColor3D ambient;
  if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_AMBIENT, ambient))
    sub->material.ambient = aiColor3D2Color(ambient);

  aiColor3D diffuse;
  if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse))
    sub->material.diffuse = aiColor3D2Color(diffuse);

  aiColor3D specular;
  if (AI_SUCCESS == material->Get(AI_MATKEY_COLOR_SPECULAR, specular))
    sub->material.specular = aiColor3D2Color(specular);

  float shininess;
  if(AI_SUCCESS == material->Get(AI_MATKEY_SHININESS, shininess))
    sub->material.shininess = (int) shininess;

  return sub;
}

Color Mesh::aiColor3D2Color(aiColor3D aicolor) {
  Color color;
  color.r = aicolor.r;
  color.g = aicolor.g;
  color.b = aicolor.b;
  return color;
}

void Mesh::Draw(Shader *shader) {
  for (SubMesh *sub : submeshes) {
    sub->Draw(shader);
  }
}
