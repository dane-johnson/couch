#include <GL/glew.h>
#include <GLFW/glfw3.h>

#ifdef LUA_SCRIPTING
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
}
#endif // LUA_SCRIPTING

#include "types.h"

class Input {
public:
  static Input *GetInstance();
  void Use(Window *window);
private:
  double lastx, lasty;
  Input();
  static void HandleKeys(Window *window, int key, int code, int action, int mods);
  static void HandleMousePosition(Window *window, double xpos, double ypos);
  static Input *instance;
};
