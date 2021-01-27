#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"
#include "Spatial.h"

class Light : public Spatial {
public:
  Vector3 color;
  float ambient, diffuse, specular;
  virtual Name GetType() const;
  virtual Light *Create();
  virtual Light *Duplicate();
  virtual Light *Instance();
};

class DirectionalLight : public Light {
public:
  Vector3 direction;
  DirectionalLight();
  DirectionalLight(Vector3 direction, Vector3 color, float ambient, float diffuse, float specular);
  virtual Name GetType() const;
  virtual DirectionalLight *Create();
  virtual DirectionalLight *Duplicate();
  virtual DirectionalLight *Instance();
};

#endif /* LIGHT_H */
