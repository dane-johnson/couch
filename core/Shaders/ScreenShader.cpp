#include "ScreenShader.h"
#include "screen.vert.h"
#include "screen.frag.h"

ScreenShader::ScreenShader() : Shader(screen_vert, screen_frag) {}
