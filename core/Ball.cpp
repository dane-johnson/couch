#include "Ball.h"

Ball::Ball() {
  // It's a cube really
  // Front
  vertices.push_back(Vertex(1.0f, 1.0f, 1.0f, 0.0f, 1.0f));
  vertices.push_back(Vertex(1.0f, -1.0f, 1.0f, 0.0f, 0.0f));
  vertices.push_back(Vertex(-1.0f, 1.0f, 1.0f, 1.0f, 1.0f));
  vertices.push_back(Vertex(-1.0f, -1.0f, 1.0f, 1.0f, 0.0f));
  // Back
  vertices.push_back(Vertex(1.0f, 1.0f, -1.0f, 0.0f, 0.0f));
  vertices.push_back(Vertex(1.0f, -1.0f, -1.0f, 0.0f, 1.0f));
  vertices.push_back(Vertex(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f));
  vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f, 1.0f, 1.0f));

  //Front
  indices.push_back(Index(0, 1, 2));
  indices.push_back(Index(1, 2, 3));
  //Back
  indices.push_back(Index(4, 5, 6));
  indices.push_back(Index(5, 6, 7));
  // Top
  indices.push_back(Index(0, 4, 6));
  indices.push_back(Index(0, 2, 6));
  // Bottom
  indices.push_back(Index(1, 3, 7));
  indices.push_back(Index(1, 5, 7));
  // Left side
  indices.push_back(Index(0, 1, 5));
  indices.push_back(Index(0, 4, 5));
  // Right side
  indices.push_back(Index(2, 3, 7));
  indices.push_back(Index(2, 6, 7));
}

