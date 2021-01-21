#include "Light.h"

Name Light::GetType() const {return "Light";}

Name DirectionalLight::GetType() const {return "DirectionalLight";}

DirectionalLight::DirectionalLight() {
  this->direction = Vector3(0.0f);
  this->color = Vector3(0.0f);
  this->ambient = 0.0f;
  this->diffuse = 0.0f;
  this->specular = 0.0f;
}

DirectionalLight::DirectionalLight(Vector3 direction, Vector3 color, cfloat ambient, cfloat diffuse, cfloat specular) {
  this->direction = direction;
  this->color = color;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
}
