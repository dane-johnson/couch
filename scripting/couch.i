%module couch

%typemap(in) cfloat {
  $1 = (cfloat) lua_tonumber(L, $input);
 }
%{
#include "Transform.h"
#include "Mesh.h"
#include "Ball.h"
#include "Camera.h"
extern void AddMeshToList(Mesh &mesh);
%}
struct Vector3 {
  double x, y, z;
};
%include "Transform.h"
%include "Mesh.h"
%include "Ball.h"
%include "Camera.h"

extern void AddMeshToList(Mesh &mesh);
