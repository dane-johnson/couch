#include "Mesh.h"

Mesh::Mesh() {
  material = new Material();
}

Mesh::~Mesh() {
  if (material) {
    delete material;
  }
}

Mesh::Mesh(VertexList vertices, IndexList indices) {
  this->vertices = vertices;
  this->indices = indices;
}

void Mesh::SetupMesh() {
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
  // Vertex UV
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
  // TODO normals

  glBindVertexArray(0);
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
  aiMesh *mesh_to_import = scene->mMeshes[root->mMeshes[0]];

  return aiMesh2Mesh(mesh_to_import);
}

Mesh *Mesh::aiMesh2Mesh(aiMesh *aimesh){
  Mesh *mymesh = new Mesh();
  for (int i = 0; i < aimesh->mNumVertices; i++) {
    aiVector3D aiPosition = aimesh->mVertices[i];
    aiVector3D aiUV = aimesh->mTextureCoords[0][i]; // TODO get ALL texture coords
    Vertex vertex(aiPosition.x, aiPosition.y, aiPosition.z, aiUV.x, aiUV.y);
    mymesh->vertices.push_back(vertex);
  }
  for (int i = 0; i < aimesh->mNumFaces; i++) {
    // We're importing triangulated meshes, so each face is three indices
    unsigned int *face = aimesh->mFaces[i].mIndices;
    Index index(face[0], face[1], face[2]);
    mymesh->indices.push_back(index);
  }
  return mymesh;
}


void Mesh::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
