%module couch

%typemap(in) cfloat {
  $1 = (cfloat) lua_tonumber(L, $input);
 }
%{
#include "Node.h"
#include "Transform.h"
#include "Spatial.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Ball.h"
#include "Camera.h"
%}
typedef float cfloat;
struct Vector3 {
  cfloat x, y, z;
};
%include "Node.h"
%include "Spatial.h"
%include "Transform.h"
%include "Drawable.h"
%include "Mesh.h"
%include "Ball.h"
%include "Camera.h"
