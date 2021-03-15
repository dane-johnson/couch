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
