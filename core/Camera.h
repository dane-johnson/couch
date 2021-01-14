#ifndef CAMERA_H
#define CAMERA_H

#include "Spatial.h"

class Camera : public Spatial {
public:
  Camera();
  void MakeCurrent();
  static Camera *GetCurrentCamera();
private:
  static Camera *currentCamera;
};

#endif /* CAMERA_H */
