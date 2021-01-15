#ifndef COUCH_H
#define COUCH_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "types.h"

typedef void (*KeyHandler)(Window *window, int key, int code, int action, int mods);
typedef void (*MousePositionHandler)(Window *window, double xpos, double ypos, double xrel, double yrel);

class Input {
public:
  static Input *GetInstance();
  void Use(Window *window);
  std::vector<KeyHandler> keyHandlers;
  std::vector<MousePositionHandler> mousePositionHandlers;
private:
  double lastx, lasty;
  Input();
  static void HandleKeys(Window *window, int key, int code, int action, int mods);
  static void HandleMousePosition(Window *window, double xpos, double ypos);
  static Input *instance;
};

#endif // COUCH_H
