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
#ifdef LUA_SCRIPTING
  lua_State *L = (lua_State*) glfwGetWindowUserPointer(window);
  lua_getglobal(L, "onkey");
  lua_pushinteger(L, keys);
  lua_pushinteger(L, code);
  lua_pushinteger(L, action);
  lua_pushinteger(L, mods);
  lua_call(L, 4, 0);
#endif // LUA_SCRIPTING
}

void Input::HandleMousePosition(Window *window, double xpos, double ypos) {
  double relx = xpos - instance->lastx;
  double rely = ypos - instance->lasty;
#ifdef LUA_SCRIPTING
  lua_State *L = (lua_State*) glfwGetWindowUserPointer(window);
  lua_getglobal(L, "onmousemotion");
  lua_pushnumber(L, xpos);
  lua_pushnumber(L, ypos);
  lua_pushnumber(L, relx);
  lua_pushnumber(L, rely);
  lua_call(L, 4, 0);
#endif // LUA_SCRIPTING
  instance->lastx = xpos;
  instance->lasty = ypos;
}
