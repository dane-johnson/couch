project(Couch)

## Find OPENGL packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

## Find Bullet
find_package(Bullet REQUIRED)

## Find Lua
find_package(Lua REQUIRED)

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
  Scripting/Lua.h
  Scripting/Lua.cpp
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

target_include_directories(couchlib
  PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR})

target_include_directories(couchlib
  PUBLIC
  ${BULLET_INCLUDE_DIRS})

if(NOT WIN32)
  target_link_libraries(couchlib glfw)
endif()
target_link_libraries(couchlib OpenGL::GL)
target_link_libraries(couchlib GLEW::GLEW)
target_link_libraries(couchlib ${LUA_LIBRARIES})
target_link_libraries(couchlib ${BULLET_LIBRARIES})

## Add documentation
find_package(Doxygen REQUIRED
  OPTIONAL_COMPONENTS dot mscgen dia)
doxygen_add_docs(Node.h)

