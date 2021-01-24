#ifndef SPATIAL_H
#define SPATIAL_H

#include "Node.h"
#include "Transform.h"

class Spatial : public Node {
public:
  Transform transform;
  virtual bool IsTransformable() const { return true;}
  virtual Name GetType() const;
  virtual Spatial *Create();
  virtual Spatial *Duplicate();  
  virtual Spatial *Instance();
};

#endif /* SPATIAL_H */
