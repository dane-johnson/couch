#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include <glm/gtc/type_ptr.hpp>

#include "types.h"
#include "Material.h"

class Shader {
public:
  Id id;

  Shader(const char *vertexPath, const char *fragmentPath);
  void Use();
  void UpdateView(Matrix view);
  void UpdateModel(Matrix model);
  void UpdateProjection(Matrix projection);
  void UpdateColor(bool usesColor);
  void UpdateColor(bool usesColor, Color color);
  void UpdateTex(bool usesTex);
  void UpdateTex(bool usesTex, Texture tex);

  virtual Name GetName() const;
};

#endif /* SHADER_H */
