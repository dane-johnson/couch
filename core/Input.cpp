#include "Input.h"

Input::Input() {}

Input *Input::instance = nullptr;

Input *Input::GetInstance() {
  if (!instance) {
    instance = new Input();
  }
  return instance;
}

void Input::Use(Window *window){
  glfwSetKeyCallback(window, (GLFWkeyfun)HandleKeys);
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
