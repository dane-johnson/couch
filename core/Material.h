#ifndef MATERIAL_H
#define MATERIAL_H

#include <GL/glew.h>
#include "stb_image.h"

#include "types.h"
#include "Util.h"

typedef Vector3 Color;

class Texture {
public:
  int width, height;
  Id id;
  static Texture FromFile(const char *filename);
  Texture();
};

struct Material {
  Texture tex;
  bool usesTex;

  Color ambient;
  Color diffuse;
  Color specular;
  
  int shininess;
  
  float alphaScissor;
  bool unshaded;
  bool cullBack;
  Material();
};

#endif /* MATERIAL_H */
