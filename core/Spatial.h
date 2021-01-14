#ifndef SPATIAL_H
#define SPATIAL_H

#include "Node.h"
#include "Transform.h"

class Spatial : virtual public Node {
public:
  Transform transform;
  virtual bool IsTransformable() const { return true;}
};

#endif /* SPATIAL_H */
