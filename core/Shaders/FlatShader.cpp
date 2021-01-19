#include "FlatShader.h"
#include "flat.vert.h"
#include "flat.frag.h"

FlatShader::FlatShader() : Shader(flat_vert, flat_frag) {}

void FlatShader::UpdateColor(Vector3 color) {
  glUniform3f(glGetUniformLocation(id, "color"), color.r, color.g, color.b);
}