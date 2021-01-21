#ifndef SPATIAL_H
#define SPATIAL_H

#include "Node.h"
#include "Transform.h"

class Spatial : public Node {
public:
  Transform transform;
  virtual bool IsTransformable() const { return true;}
  virtual Name GetType() const;
};

#endif /* SPATIAL_H */
