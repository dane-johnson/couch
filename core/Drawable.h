#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Node.h"

class Drawable : virtual public Node {
public:
  virtual bool IsDrawable() const {return true;}
  virtual void Draw() = 0;
};

#endif /* DRAWABLE_H */
