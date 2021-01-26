#ifndef SKYBOXSHADER_H
#define SKYBOXSHADER_H

#include "Shader.h"
#include "../Skybox.h"

class SkyboxShader : public Shader {
public:
  SkyboxShader();
  Name GetName() const;
  void UpdateSkybox(Skybox skybox);
};

#endif /* SKYBOXSHADER_H */
