#ifndef MATERIAL_H
#define MATERIAL_H

#include <iostream>
#include <stdlib.h>

#include <GL/glew.h>
#include "stb_image.h"

#include "types.h"

struct Color {
  cfloat r, g, b;
  Color();
  Color(cfloat r, cfloat g, cfloat b);
};

class Texture {
public:
  int width, height;
  Id id;
  static Texture FromFile(const char *filename);
  Texture();
};

struct Material {
  Color color;
  bool usesColor;
  Texture tex;
  bool usesTex;
  Material();
};

#endif /* MATERIAL_H */
