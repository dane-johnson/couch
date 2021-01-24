#include "Spatial.h"

Name Spatial::GetType() const {return "Spatial";}

Spatial *Spatial::Create() {
  return new Spatial;
}

Spatial *Spatial::Duplicate() {
  Spatial *spatial = static_cast<Spatial*>(Node::Duplicate());
  spatial->transform = transform;

  return spatial;
}

Spatial *Spatial::Instance() {
  return static_cast<Spatial*>(Node::Instance());
}

