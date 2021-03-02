// NOTE: Do this here and only here, stbi will be defined where
// this macro is included
#define STB_IMAGE_IMPLEMENTATION

#include "Material.h"

#include <string>

Texture::Texture() {}

Texture Texture::FromFile(const char *filename) {
  Texture tex;
  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int nrChannels;
  unsigned char* data = stbi_load(filename, &tex.width, &tex.height, &nrChannels, 4);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex.width, tex.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    throw std::string() + "Error loading texture file: " + filename;
  }

  stbi_image_free(data);

  return tex;
}

Material::Material() {
  usesTex = false;

  shininess = 8;
  
  alphaScissor = 0.0f;
  unshaded = false;
  cullBack = true;
}
