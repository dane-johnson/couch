#include "Mesh.h"

Mesh::Mesh() {
  material = new Material();
}

Mesh::~Mesh() {
  delete material;
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

Mesh Mesh::FromFile(const char *filename) {
  return Mesh();
}

void Mesh::Draw() {
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, indices.size() * 3, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
