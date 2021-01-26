#ifndef SCRIPTINGLANGUAGE_H
#define SCRIPTINGLANGUAGE_H

#include "../types.h"

class ScriptingLanguage {
public:
  virtual void Initialize() = 0;
  virtual void Update(double delta) = 0;
  virtual void Close() = 0;
  virtual bool HasHook(const char * name) = 0;
  static ScriptingLanguage *GetCurrentLanguage();
protected:
  static ScriptingLanguage *language;
};

#endif /* SCRIPTINGLANGUAGE_H */
