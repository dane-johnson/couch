#include "Camera.h"

Camera::Camera() {
  if (!currentCamera) {
    currentCamera = this;
  }
}

void Camera::MakeCurrent() {
  currentCamera = this;
}

Camera*Camera::GetCurrentCamera() {
  return currentCamera;
}

Camera *Camera::currentCamera = nullptr;
