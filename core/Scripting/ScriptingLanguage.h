#ifndef SCRIPTINGLANGUAGE_H
#define SCRIPTINGLANGUAGE_H

class ScriptingLanguage {
public:
  virtual void Initialize() = 0;
  virtual void Update(double delta) = 0;
  virtual void Close() = 0;
  virtual void Error() = 0;
  static ScriptingLanguage *GetCurrentLanguage();
protected:
  static ScriptingLanguage *language;
};

#endif /* SCRIPTINGLANGUAGE_H */
