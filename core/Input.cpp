#include "Input.h"

Input::Input() {}

Input *Input::instance = nullptr;

Input *Input::GetInstance() {
  if (!instance) {
    instance = new Input();
    instance->lastx = 0.0;
    instance->lasty = 0.0;
  }
  return instance;
}


void Input::Use(Window window){
  glfwSetInputMode(window.glfwWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(window.glfwWindow, (GLFWkeyfun)HandleKeys);
  glfwSetCursorPosCallback(window.glfwWindow, (GLFWcursorposfun)HandleMousePosition);
}

void Input::HandleKeys(GLFWwindow *_, int keys, int code, int action, int mods) {
  for (KeyHandler keyHandler : instance->keyHandlers) {
    keyHandler(keys, code, action, mods);
  }
}

void Input::HandleMousePosition(GLFWwindow *_, double xpos, double ypos) {
  double relx, rely;
  if (instance->firstMousePositionUpdate) {
    relx = 0.0;
    rely = 0.0;
    instance->firstMousePositionUpdate = false;
  } else {
    relx = xpos - instance->lastx;
    rely = ypos - instance->lasty;
  }
  for (MousePositionHandler mousePositionHandler : instance->mousePositionHandlers) {
    mousePositionHandler(xpos, ypos, relx, rely);
  }
  instance->lastx = xpos;
  instance->lasty = ypos;
}
