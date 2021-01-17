#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Node.h"
#include "Material.h"

class Drawable : virtual public Node {
public:
  virtual bool IsDrawable() const {return true;}
  virtual void Draw() = 0;
  Material *material;
};

#endif /* DRAWABLE_H */
