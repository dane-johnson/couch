#ifndef CAMERA_H
#define CAMERA_H

#include "Transform.h"

class Camera {
public:
  Camera();
  Transform transform;
  void MakeCurrent();
  static Camera *GetCurrentCamera();
private:
  static Camera *currentCamera;
};

#endif /* CAMERA_H */
