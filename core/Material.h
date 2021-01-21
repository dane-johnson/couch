#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "stb_image.h"

#include "types.h"
#include "Util.h"

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
  cfloat alphaScissor;
  bool unshaded;
  Material();
};

#endif /* MATERIAL_H */
