project(Couch)


## STB (image)
target_include_directories(couch
  PUBLIC stb)
target_include_directories(couchlua
  PUBLIC stb)

## ASSIMP
set(ASSIMP_BUILD_ALL_IMPORTERS_BY_DEFAULT FALSE CACHE BOOL "Turn off all assimp importers")
set(ASSIMP_BUILD_GLTF_IMPORTER ON CACHE BOOL "Turn on gltf importer")
add_subdirectory(assimp)
target_link_libraries(couch assimp::assimp)
target_link_libraries(couchlua assimp::assimp)
