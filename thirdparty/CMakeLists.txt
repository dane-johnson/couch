project(Couch)

## STB (image)
target_include_directories(couchlib
  PUBLIC stb)

## ASSIMP
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE CACHE BOOL "Turn off all assimp importers")
set(ASSIMP_BUILD_OBJ_IMPORTER ON CACHE BOOL "Turn on wavefront importer")
add_subdirectory(assimp)
target_link_libraries(couchlib assimp::assimp)

