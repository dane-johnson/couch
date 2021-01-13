#include "Ball.h"

Ball::Ball() {
  vertices.push_back(Vertex(1.0f, 1.0f, -1.0f));
  vertices.push_back(Vertex(1.0f, -1.0f, -1.0f));
  vertices.push_back(Vertex(-1.0f, 1.0f, -1.0f));
  vertices.push_back(Vertex(-1.0f, -1.0f, -1.0f));

  indices.push_back(Index(0, 1, 2));
  indices.push_back(Index(1, 2, 3));
}

