%module couch

%include "typemaps.i"

%{
#include "types.h"
#include "Node.h"
#include "Transform.h"
#include "Spatial.h"
#include "Drawable.h"
#include "Mesh.h"
#include "Ball.h"
#include "Camera.h"
  %}

typedef float cfloat;
%ignore "cfloat";

class Vector3 {
public:
  cfloat x, y, z;
};
%ignore "Vector3";

%include "types.h"
%include "Node.h"
%include "Spatial.h"
%include "Transform.h"
%include "Drawable.h"
%include "Mesh.h"
%include "Ball.h"
%include "Camera.h"

