#include "Light.h"

Name Light::GetType() const {return "Light";}

Light *Light::Duplicate() {
  Light *light = static_cast<Light*>(Spatial::Duplicate());
  light->color = color;
  light->ambient = ambient;
  light->diffuse = diffuse;
  light->specular = specular;

  return light;
}

Light *Light::Instance() {
  return static_cast<Light*>(Node::Instance());
}

Light *Light::Create() {
  return new Light;
}

Name DirectionalLight::GetType() const {return "DirectionalLight";}

DirectionalLight::DirectionalLight() {
  this->direction = Vector3(0.0f);
  this->color = Vector3(0.0f);
  this->ambient = 0.0f;
  this->diffuse = 0.0f;
  this->specular = 0.0f;
}

DirectionalLight::DirectionalLight(Vector3 direction, Vector3 color, float ambient, float diffuse, float specular) {
  this->direction = direction;
  this->color = color;
  this->ambient = ambient;
  this->diffuse = diffuse;
  this->specular = specular;
}

DirectionalLight *DirectionalLight::Create() {
  return new DirectionalLight;
}

DirectionalLight *DirectionalLight::Duplicate() {
  DirectionalLight *directionalLight = static_cast<DirectionalLight*>(Light::Duplicate());
  directionalLight->direction = direction;

  return directionalLight;
}

DirectionalLight *DirectionalLight::Instance() {
  return static_cast<DirectionalLight*>(Node::Instance());
}
