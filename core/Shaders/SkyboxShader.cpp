#include "SkyboxShader.h"
#include "skybox.vert.h"
#include "skybox.frag.h"

SkyboxShader::SkyboxShader() : Shader(skybox_vert, skybox_frag) {}

void SkyboxShader::UpdateSkybox(Skybox skybox) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox.id);
}

Name SkyboxShader::GetName() const { return "Skybox Shader"; }
