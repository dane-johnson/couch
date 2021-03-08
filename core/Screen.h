#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>

#include "types.h"
#include "Vertex.h"
#include "Material.h"

class Screen {
public:
  Screen();
  void Enable();
  void Draw();
  const int width = 640;
  const int height = 480;
  Texture tex;
private:
  Id quad;
  Id framebuffer;
  Id renderbuffer;
};

#endif /* SCREEN_H */
