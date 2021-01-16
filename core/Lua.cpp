#include "Lua.h"

#ifdef LUA_SCRIPTING

lua_State *Lua::L { luaL_newstate() };

#endif // LUA_SCRIPTING

void Lua::Initialize() {
#ifdef LUA_SCRIPTING
  language = this;
  int err;
  // Initialize Lua
  luaL_openlibs(L);
  luaopen_couch(L);
  err = luaL_loadfile(L, "main.lua");
  if (err == LUA_OK) {
    err = lua_pcall(L, 0, 0, 0);
    if (err != LUA_OK) {
      Error();
    }
    lua_getglobal(L, "init");
    err = lua_pcall(L, 0, 0, 0);
    if (err != LUA_OK) {
      Error();
    }
  } else if (err == LUA_ERRFILE) {
    std::cerr << "Could not find main.lua." << std::endl;
    exit(1);
  } else {
    // Syntax error
    Error();
  }

  // Bind input functions
  //glfwSetWindowUserPointer(window, (void*) L);
  Input *input = Input::GetInstance();
  input->keyHandlers.push_back(LuaKeyHandler);
  input->mousePositionHandlers.push_back(LuaMousePositionHandler);
#else // LUA_SCRIPTING
  std::cerr << "Lua is selected as scripting language, but this binary was built without Lua support." << std::endl;
  exit(1);
#endif // LUA_SCRIPTING
}

void Lua::Update(double delta) {
#ifdef LUA_SCRIPTING
  lua_getglobal(L, "update");
  lua_pushnumber(L, delta);
  lua_call(L, 1, 0);
#endif // LUA_SCRIPTING
}

void Lua::Close() {
#ifdef LUA_SCRIPTING
  lua_close(L);
#endif // LUA_SCRIPTING
}

void Lua::Error() {
#ifdef LUA_SCRIPTING
  const char *error = lua_tolstring(L, -1, 0);
  std::cerr << error << std::endl;
#endif // LUA_SCRIPTING
  exit(1);
}

void Lua::LuaKeyHandler(Window *window, int key, int code, int action, int mods) {
#ifdef LUA_SCRIPTING
  // lua_State *L = (lua_State*) glfwGetWindowUserPointer(window);
  lua_getglobal(L, "onkey");
  lua_pushinteger(L, key);
  lua_pushinteger(L, code);
  lua_pushinteger(L, action);
  lua_pushinteger(L, mods);
  lua_call(L, 4, 0);
#endif // LUA_SCRIPTING
}

void Lua::LuaMousePositionHandler(Window *window, double xpos, double ypos, double relx, double rely) {
#ifdef LUA_SCRIPTING
  // lua_State *L = (lua_State*) glfwGetWindowUserPointer(window);
  lua_getglobal(L, "onmousemotion");
  lua_pushnumber(L, xpos);
  lua_pushnumber(L, ypos);
  lua_pushnumber(L, relx);
  lua_pushnumber(L, rely);
  lua_call(L, 4, 0);
#endif // LUA_SCRIPTING
}
