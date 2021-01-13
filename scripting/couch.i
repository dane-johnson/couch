%module couch

%typemap(in) cfloat {
  $1 = (cfloat) lua_tonumber(L, $input);
}

%{
#include "types.h"
#include "Transform.h"
#include "Mesh.h"
#include "Ball.h"
#include "Camera.h"
extern void AddMeshToList(Mesh &mesh);
%}
%include "types.h"
%include "Transform.h"
%include "Mesh.h"
%include "Ball.h"
%include "Camera.h"
extern void AddMeshToList(Mesh &mesh);
