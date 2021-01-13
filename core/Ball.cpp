#include "Ball.h"

Ball::Ball() {
  vertices.push_back(Vertex(0.0f, 0.0f, 0.0f));
  vertices.push_back(Vertex(1.0f, 0.0f, 0.0f));
  vertices.push_back(Vertex(0.5f, 1.0f, 0.0f));

  indices.push_back(Index(0, 1, 2));
}

