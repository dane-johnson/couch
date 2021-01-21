#ifndef FLATSHADER_H
#define FLATSHADER_H

#include "Shader.h"

class FlatShader : public Shader {
public:
  FlatShader();
  Name GetName() const;
};

#endif /* FLATSHADER_H */

