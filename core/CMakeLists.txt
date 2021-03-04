project(Couch)

## Find OPENGL packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

## Find Bullet
find_package(Bullet REQUIRED)

## Find AssImp
find_package(ASSIMP REQUIRED)

if (LUA_ENABLED)
## Find Lua
find_package(Lua REQUIRED)
endif ()

add_library(couchlib SHARED)
target_sources(couchlib PUBLIC
  Camera.h
  Camera.cpp
  CollisionShape.h
  CollisionShape.cpp
  constants.h
  Index.h
  Index.cpp
  Input.h
  Input.cpp
  Light.h
  Light.cpp
  Material.h
  Material.cpp
  Mesh.h
  Mesh.cpp
  Node.h
  Node.cpp
  Rigidbody.h
  Rigidbody.cpp
  Screen.h
  Screen.cpp
  Skybox.h
  Skybox.cpp
  Spatial.h
  Spatial.cpp
  Transform.h
  Transform.cpp
  types.h
  types.cpp
  Util.h
  Util.cpp
  Vertex.h
  Vertex.cpp
  World.h
  World.cpp
  Scripting/ScriptingLanguage.h
  Scripting/ScriptingLanguage.cpp
  Shaders/FlatShader.h
  Shaders/FlatShader.cpp
  Shaders/ScreenShader.h
  Shaders/ScreenShader.cpp
  Shaders/Shader.h
  Shaders/Shader.cpp
  Shaders/SkyboxShader.h
  Shaders/SkyboxShader.cpp)


if (WIN32)
  add_library(couchlib_luascripting STATIC)
else ()
  add_library(couchlib_luascripting SHARED)
endif ()
target_sources(couchlib_luascripting PUBLIC
  Scripting/Lua.h
  Scripting/Lua.cpp)
target_link_libraries(couchlib_luascripting couchlua)


target_include_directories(couchlib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(couchlib
  PUBLIC
  ${BULLET_INCLUDE_DIRS})

target_include_directories(couchlib
  PUBLIC
  ${ASSIMP_INCLUDE_DIR})

target_link_libraries(couchlib glfw)
target_link_libraries(couchlib OpenGL::GL)
target_link_libraries(couchlib GLEW::GLEW)
if (LUA_ENABLED)
  target_link_libraries(couchlib_luascripting ${LUA_LIBRARIES})
endif () 
target_link_libraries(couchlib ${BULLET_LIBRARIES})
target_link_libraries(couchlib ${ASSIMP_LIBRARY})

## Add documentation
find_package(Doxygen REQUIRED
  OPTIONAL_COMPONENTS dot mscgen dia)
doxygen_add_docs(couchdocs
  .
  mainpage.dox)
