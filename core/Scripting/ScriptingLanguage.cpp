#include "ScriptingLanguage.h"

ScriptingLanguage *ScriptingLanguage::language { nullptr };

ScriptingLanguage *ScriptingLanguage::GetCurrentLanguage() {
  return language;
}

