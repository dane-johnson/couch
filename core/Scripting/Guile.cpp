#include "Guile.h"

#include "../Util.h"

void Guile::Initialize() {
#ifdef GUILE_SCRIPTING
  language = this;
  // Initialize Guile
  scm_with_guile(Guile::inner_init, NULL);

  // Bind input functions
  Input *input = Input::GetInstance();
  if (HasHook("onkey")) {
    input->keyHandlers.push_back(GuileKeyHandler);
  }
  if (HasHook("onmousemotion")) {
    input->mousePositionHandlers.push_back(GuileMousePositionHandler);
  }
#else // GUILE_SCRIPTING
  Util::Die("Guile is selected as the scripting language, but this binary was built without Guile support.");
#endif // GUILE_SCRIPTING
}

void Guile::Update(double delta) {
#ifdef GUILE_SCRIPTING
  if (HasHook("update")) {
    scm_with_guile(Guile::inner_update, &delta);
  }
#endif // GUILE_SCRIPTING
}

void Guile::Close() {
  // Nothing to do
}

bool Guile::HasHook(const char *name) {
  bool exists = false;
#ifdef GUILE_SCRIPTING
  exists = scm_with_guile(Guile::inner_has_hook, (void *) name);
#endif // GUILE_SCRIPTING
  return exists;
}

#ifdef GUILE_SCRIPTING

void Guile::GuileKeyHandler(int key, int code, int action, int mods) {
  Guile::key_event ev {key, code, action, mods};
  scm_with_guile(Guile::inner_key_handler, &ev);
}

void Guile::GuileMousePositionHandler(double xpos, double ypos, double relx, double rely) {
  Guile::mouse_position_event ev {xpos, ypos, relx, rely};
  scm_with_guile(Guile::inner_mouse_position_handler, &ev);
}

void *Guile::inner_init(void* empty) {
  // Init swig
  SWIG_init();
  // Load main file
  scm_c_primitive_load("main.scm");
  // Execute the init function if it exists
  if (ScriptingLanguage::language->HasHook("init")) {
    scm_call_0(scm_c_eval_string("init"));
  }
}

void *Guile::inner_update(void *data) {
  double delta = *(double*) data;
  if (ScriptingLanguage::language->HasHook("update")) {
    scm_call_1(scm_c_eval_string("update"), scm_from_double(delta));
  }
}

void *Guile::inner_has_hook(void *data) {
  const char *name = (const char *) data;
  return (void *) scm_to_bool(scm_defined_p(scm_from_locale_symbol(name), SCM_UNDEFINED));
}

void *Guile::inner_key_handler(void *data) {
  Guile::key_event *ev = (Guile::key_event*) data;
  if (ScriptingLanguage::language->HasHook("onkey")) {
    scm_call_4(scm_c_eval_string("onkey"),
	       scm_from_int(ev->key),
	       scm_from_int(ev->code),
	       scm_from_int(ev->action),
	       scm_from_int(ev->mods));
  }
}

void *Guile::inner_mouse_position_handler(void *data) {
  Guile::mouse_position_event *ev = (Guile::mouse_position_event *) data;
  if (ScriptingLanguage::language->HasHook("onmousemotion")) {
    scm_call_4(scm_c_eval_string("onmousemotion"),
	       scm_from_double(ev->xpos),
	       scm_from_double(ev->ypos),
	       scm_from_double(ev->relx),
	       scm_from_double(ev->rely));
  }
}


#endif // GUILE_SCRIPTING

