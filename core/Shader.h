#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "types.h"

class Shader {
public:
  Id id;

  Shader(const char *vertexPath, const char *fragmentPath);
  void Use();
};

#endif /* SHADER_H */
