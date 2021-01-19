#include "Material.h"

Color::Color() {
  this->r = 0.0f;
  this->g = 0.0f;
  this->b = 0.0f;
}

Color::Color(cfloat r, cfloat g, cfloat b) {
  this->r = r;
  this->g = g;
  this->b = b;
}

Texture::Texture() {}

Texture Texture::FromFile(const char *filename) {
  // Lotta hocus pocus
  // https://learnopengl.com/Getting-started/Textures
  Texture tex;
  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int nrChannels;
  unsigned char* data = stbi_load(filename, &tex.width, &tex.height, &nrChannels, 0);
  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.width, tex.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cout << "Error loading texture file: " << filename << std::endl;
    exit(1);
  }

  stbi_image_free(data);

  return tex;
}

Material::Material() {
  usesColor = false;
  usesTex = false;
}
