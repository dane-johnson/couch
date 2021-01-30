#include "Lua.h"

#include <string>

#include "../Util.h"

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
  lua_atpanic(L, &LuaExceptionHandler);

  err = luaL_loadfile(L, "main.lua");
  if (err == LUA_OK) {
    lua_call(L, 0, 0);
    if (HasHook("init")) {
      lua_getglobal(L, "init");
      lua_call(L, 0, 0);
    }
  } else if (err == LUA_ERRFILE) {
    Util::Die("Could not find main.lua.");
  } else {
    // Syntax error
    Error();
  }

  // Bind input functions
  //glfwSetWindowUserPointer(window, (void*) L);
  Input *input = Input::GetInstance();
  if (HasHook("onkey")) {
    input->keyHandlers.push_back(LuaKeyHandler);
  }
  if (HasHook("onmousemotion")) {
    input->mousePositionHandlers.push_back(LuaMousePositionHandler);
  }
#else // LUA_SCRIPTING
  Util::Die("Lua is selected as scripting language, but this binary was built without Lua support.");
#endif // LUA_SCRIPTING
}

void Lua::Update(double delta) {
#ifdef LUA_SCRIPTING
  if (HasHook("update")) {
    lua_getglobal(L, "update");
    lua_pushnumber(L, delta);
    lua_call(L, 1, 0);
  }
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
  Util::Die(error);
#endif // LUA_SCRIPTING
  Util::Die("Whut?");
}

bool Lua::HasHook(const char *name) {
  bool exists = false;
#ifdef LUA_SCRIPTING
  int type = lua_getglobal(L, name);
  lua_pop(L, -1);
  exists = type != LUA_TNIL;
#endif // LUA_SCRIPTING
  return exists;
}

#ifdef LUA_SCRIPTING

void Lua::LuaKeyHandler(Window *window, int key, int code, int action, int mods) {
  lua_getglobal(L, "onkey");
  lua_pushinteger(L, key);
  lua_pushinteger(L, code);
  lua_pushinteger(L, action);
  lua_pushinteger(L, mods);
  lua_call(L, 4, 0);
}

void Lua::LuaMousePositionHandler(Window *window, double xpos, double ypos, double relx, double rely) {
  // lua_State *L = (lua_State*) glfwGetWindowUserPointer(window);
  lua_getglobal(L, "onmousemotion");
  lua_pushnumber(L, xpos);
  lua_pushnumber(L, ypos);
  lua_pushnumber(L, relx);
  lua_pushnumber(L, rely);
  lua_call(L, 4, 0);
}

int Lua::LuaExceptionHandler(lua_State *L1) {
  std::string err;
  err += lua_tostring(L1, -1);
  err += "\n";
  luaL_traceback(L1, L1, NULL, 1);
  err += lua_tostring(L, -1);
  Util::Die(err);
  // Should never get here
  return 1;
}

#endif // LUA_SCRIPTING

