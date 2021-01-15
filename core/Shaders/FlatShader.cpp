#include "FlatShader.h"

FlatShader::FlatShader() : Shader("shaders/flat.vert", "shaders/flat.frag") {}

void FlatShader::UpdateColor(Vector3 color) {
  glUniform3f(glGetUniformLocation(id, "color"), color.r, color.g, color.b);
}
