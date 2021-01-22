#include "ScreenShader.h"
#include "screen.vert.h"
#include "screen.frag.h"

ScreenShader::ScreenShader() : Shader(screen_vert, screen_frag) {}

void ScreenShader::UpdateTex(Texture tex){
  glBindTexture(GL_TEXTURE_2D, tex.id);
}

Name ScreenShader::GetName() const {return "Screen Shader";}
