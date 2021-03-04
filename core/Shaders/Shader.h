#ifndef SHADER_H
#define SHADER_H

#include <glm/gtc/type_ptr.hpp>

#include "../types.h"
#include "../Material.h"
#include "../Light.h"

#define NUM_POINT_LIGHTS 4

class Shader {
public:
  Id id;

  Shader(const char *vertexCode, const char *fragmentCode);
  void Use();
  void UpdateView(Matrix view);
  void UpdateModel(Matrix model);
  void UpdateProjection(Matrix projection);
  void UpdateNormal(glm::mat3 normal);

  void UpdateMaterial(Material material);
  
  void UpdateDirectionalLight(DirectionalLight directionalLight);
  void UpdatePointLights(PointLightList pointLights);

  virtual Name GetName() const;
};

#endif /* SHADER_H */
