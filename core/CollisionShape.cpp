/*
  Dane Johnson <dane@danejohnson.org>
 
  LICENSE
 
  Couch  Copyright (C) 2021 Dane Johnson

  This program comes with ABSOLUTELY NO WARRANTY; without event the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for details at
  https://www.gnu.org/licenses/gpl-3.0.html
  
  This is free software, and you are welcome to redistribute it
  under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.
 
  DESCRIPTION
 
  Defines various collision shapes for rigidbodies and trigger areas
*/
#include "CollisionShape.h"

CollisionShape::CollisionShape() {
  shape = nullptr;
}

SphereCollisionShape::SphereCollisionShape(float radius) {
  shape = new btSphereShape(radius);
}

BoxCollisionShape::BoxCollisionShape(float width, float height, float depth) {
  shape = new btBoxShape(btVector3(width / 2.0f, height / 2.0f, depth / 2.0f));
}

CapsuleCollisionShape::CapsuleCollisionShape(float radius, float height) {
  shape = new btCapsuleShape(radius, height);
}

MeshCollisionShape::MeshCollisionShape(Mesh *mesh) {
  btCompoundShape *compoundShape = new btCompoundShape();

  for (SubMesh *submesh : mesh->submeshes) {
    btTriangleIndexVertexArray *indexVertexArray = new btTriangleIndexVertexArray(
      submesh->indices.size(),
      (int*) &submesh->indices[0],
      sizeof(Index),
      submesh->vertices.size(),
      (float*) &submesh->vertices[0],
      sizeof(Vertex)
      );
    compoundShape->addChildShape(
      btTransform::getIdentity(),
      new btBvhTriangleMeshShape(indexVertexArray, true)
      );
  }

  shape = compoundShape;
}
