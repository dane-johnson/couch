%module couch

%include "typemaps.i"
#ifdef SWIGLUA
%include "lua/helpers.i"
#endif // SWIGLUA

%{
#include "types.h"
#include "constants.h"
#include "Node.h"
#include "Transform.h"
#include "Spatial.h"
#include "Mesh.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "Skybox.h"
#include "Rigidbody.h"
#include "CollisionShape.h"
%}

typedef float cfloat;
%ignore "cfloat";

class Vector3 {
public:
  Vector3();
  Vector3(cfloat x, cfloat y, cfloat z);
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
%include "constants.h"
%include "Node.h"
%include "Spatial.h"
%include "Mesh.h"
%include "Transform.h"
%include "Material.h"
%include "Camera.h"
%include "Light.h"
%include "Skybox.h"
%include "Rigidbody.h"
%include "CollisionShape.h"
