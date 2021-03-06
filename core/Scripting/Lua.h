#ifndef LUA_H
#define LUA_H

#include "../Input.h"

#ifdef LUA_SCRIPTING
// Lua includes
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"  
}
extern "C" int luaopen_couch(lua_State* L);
#endif // LUA_SCRIPTING

#include "ScriptingLanguage.h"

class Lua : public ScriptingLanguage {
public:
  void Initialize();
  void Update(double delta);
  void Close();
  static void Error();
  bool HasHook(const char *name);
private:
#ifdef LUA_SCRIPTING
  static lua_State *L;
  static void LuaKeyHandler(int key, int code, int action, int mods);
  static void LuaMousePositionHandler(double xpos, double ypos, double xrel, double yrel);
  static int LuaExceptionHandler(lua_State *L1);
#endif // LUA_SCRIPTING
};

#endif /* LUA_H */
