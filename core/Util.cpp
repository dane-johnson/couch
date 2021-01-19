#include "Util.h"

Mesh *Util::aiMesh2Mesh(aiMesh *aimesh){
  Mesh *mymesh = new Mesh();
  for (int i = 0; i < aimesh->mNumVertices; i++) {
    aiVector3D aiPosition = aimesh->mVertices[i];
    aiVector3D aiUV = aimesh->mTextureCoords[0][i]; // TODO get ALL texture coords
    Vertex vertex(aiPosition.x, aiPosition.y, aiPosition.z, aiUV.x, aiUV.y);
    mymesh->vertices.push_back(vertex);
  }
  for (int i = 0; i < aimesh->mNumFaces; i++) {
    // We're importing triangulated meshes, so each face is three indices
    unsigned int *face = aimesh->mFaces[i].mIndices;
    Index index(face[0], face[1], face[2]);
    mymesh->indices.push_back(index);
  }
  return mymesh;
}
