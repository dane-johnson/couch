#include "FlatShader.h"
#include "flat.vert.h"
#include "flat.frag.h"

FlatShader::FlatShader() : Shader(flat_vert, flat_frag) {}

Name FlatShader::GetName() const {return "Flat Shader";}
