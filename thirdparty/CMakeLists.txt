project(Couch)

## STB (image)
target_include_directories(couchlib
  PUBLIC stb)

## ASSIMP
add_subdirectory(assimp)
target_include_directories(couchlib
  PUBLIC
  assimp/include)
target_link_libraries(couchlib assimp::assimp)

## Bullet
add_subdirectory(bullet)
target_include_directories(couchlib
  PUBLIC
  bullet/src)
target_link_libraries(couchlib LinearMath Bullet3Common BulletCollision BulletDynamics)
