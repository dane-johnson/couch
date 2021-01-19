#ifndef UTIL_H
#define UTIL_H

// Thirdparty includes
#include <assimp/mesh.h>

// Gahhhhhh mutual inclusion!
#include "Mesh.h"
class Mesh;

namespace Util {
  Mesh *aiMesh2Mesh(aiMesh *mesh);
}

#endif /* UTIL_H */
