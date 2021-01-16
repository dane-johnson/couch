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
  Vector3();
  cfloat x, y, z;
};
%extend Vector3 {
  Vector3 operator+(const Vector3 &o) const {
    return *$self + o;
  }
  Vector3 operator*(const cfloat &o) const {
    return *$self * o;
  }
}
%ignore "Vector3";

%include "types.h"
%include "Node.h"
%include "Spatial.h"
%include "Transform.h"
%include "Drawable.h"
%include "Mesh.h"
%include "Ball.h"
%include "Camera.h"

