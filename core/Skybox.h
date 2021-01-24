#ifndef SKYBOX_H
#define SKYBOX_H

#include <GL/glew.h>

#include "types.h"
#include "Node.h"
#include "Material.h"

class Skybox : public Node {
public:
  Skybox();
  virtual Name GetType() const;
  virtual Skybox *Create();
  virtual Skybox *Duplicate();
  virtual Skybox *Instance();
  static Skybox *FromFiles(const char *right, const char* left, const char* top, const char* bottom, const char* front, const char* back);
  void DrawSkybox();
  Id id;
private:
  Id cube;
};

#endif /* SKYBOX_H */
