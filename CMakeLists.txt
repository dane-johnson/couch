cmake_minimum_required(VERSION 3.13)
project(Couch)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

set(CMAKE_CXX_FLAGS_RELEASE -O2)

option(LUA_ENABLED "Lua scripting support" ON)
if (LUA_ENABLED)
  add_compile_definitions(LUA_SCRIPTING)
  ## Find Lua
  ## Do it here because it's needed in a bunch of places and the debian cmake is a stickler
  find_package(Lua REQUIRED)
  include_directories(${LUA_INCLUDE_DIR})
endif ()
add_executable(couch core/couch.cpp)

add_subdirectory(core)
target_link_libraries(couch couchlib)
target_link_libraries(couch couchlib_luascripting)

add_subdirectory(scripting)
if (LUA_ENABLED)
  target_link_libraries(couch couchlua)
endif()

add_subdirectory(thirdparty)

add_subdirectory(shaders)
add_dependencies(couchlib shader_headers)
target_include_directories(couchlib
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/shaders/")

file(COPY LICENSE CORRESPONDINGSOURCE.txt DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

if(WIN32)
  target_link_libraries(couch glfw3dll)
  target_link_libraries(couch ssp)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif(WIN32)

install(TARGETS couch couchlib couchlib_luascripting
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
if (LUA_ENABLED)
  install(TARGETS couchlua
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
endif ()
