#include "Shader.h"

class ScreenShader : public Shader {
public:
  ScreenShader();
  Name GetName() const;
  void UpdateTex(Texture texture);
};
