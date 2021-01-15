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

void Input::Use(Window *window){
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetKeyCallback(window, (GLFWkeyfun)HandleKeys);
  glfwSetCursorPosCallback(window, (GLFWcursorposfun)HandleMousePosition);
}

void Input::HandleKeys(Window *window, int keys, int code, int action, int mods) {
  for (KeyHandler keyHandler : instance->keyHandlers) {
    keyHandler(window, keys, code, action, mods);
  }
}

void Input::HandleMousePosition(Window *window, double xpos, double ypos) {
  double relx = xpos - instance->lastx;
  double rely = ypos - instance->lasty;
  for (MousePositionHandler mousePositionHandler : instance->mousePositionHandlers) {
    mousePositionHandler(window, xpos, ypos, relx, rely);
  }
  instance->lastx = xpos;
  instance->lasty = ypos;
}
