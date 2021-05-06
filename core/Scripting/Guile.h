#ifndef GUILE_H
#define GUILE_H

#include "../Input.h"

#ifdef GUILE_SCRIPTING
#include <libguile.h>  


extern "C" void SWIG_init();
#endif // GUILE_SCRIPTING

#include "ScriptingLanguage.h"

class Guile : public ScriptingLanguage {
public:
  void Initialize();
  void Update(double delta);
  void Close();
  bool HasHook(const char *name);
private:
#ifdef GUILE_SCRIPTING
  struct key_event {
    int key;
    int code;
    int action;
    int mods;
  };
  struct mouse_position_event {
    double xpos;
    double ypos;
    double relx;
    double rely;
  };
  static void *inner_init(void *empty);
  static void *inner_update(void *delta);
  static void *inner_has_hook(void *name);
  static void *inner_key_handler(void *ev);
  static void *inner_mouse_position_handler(void *ev);
  static void GuileKeyHandler(int key, int code, int action, int mods);
  static void GuileMousePositionHandler(double xpos, double ypos, double relx, double rely);
#endif // GUILE_SCRIPTING
};


#endif /* GUILE_H */
