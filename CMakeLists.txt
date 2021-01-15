cmake_minimum_required(VERSION 3.13)
project(Couch)
set(CMAKE_MODULE_PATH, ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR/cmake.})

## Find OPENGL packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 3.3 REQUIRED)

## Find SWIG
find_package(SWIG REQUIRED)

## Find Lua
find_package(Lua REQUIRED)

file(GLOB_RECURSE sources core/*.cpp core/*.h)
file(GLOB shaders shaders/*)

add_compile_definitions(LUA_SCRIPTING)
add_executable(couch ${sources})
include_directories(core)
if(NOT WIN32)
  target_link_libraries(couch glfw)
endif()
target_link_libraries(couch OpenGL::GL)
target_link_libraries(couch GLEW::GLEW)
target_link_libraries(couch ${LUA_LIBRARIES})

file(COPY shaders DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

include(UseSWIG)
set_property(SOURCE scripting/couch.i PROPERTY CPLUSPLUS ON)
swig_add_library(couchlua
  TYPE STATIC
  LANGUAGE lua
  SOURCES scripting/couch.i)
target_link_libraries(couchlua ${LUA_LIBRARIES})
target_link_libraries(couch couchlua)

if(WIN32)
  target_link_libraries(couch glfw3dll)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif(WIN32)
