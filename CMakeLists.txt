cmake_minimum_required(VERSION 3.13)
project(Couch)
set(CMAKE_MODULE_PATH, ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR/cmake.})

add_compile_definitions(LUA_SCRIPTING)
add_executable(couch core/couch.cpp)

add_subdirectory(core)
target_link_libraries(couch couchlib)

add_subdirectory(scripting)
target_link_libraries(couch couchlua)

add_subdirectory(thirdparty)

add_subdirectory(shaders)
add_dependencies(couchlib shader_headers)
target_include_directories(couchlib
  PUBLIC "${CMAKE_CURRENT_BINARY_DIR}/shaders/")

if(WIN32)
  target_link_libraries(couch glfw3dll)
  target_link_libraries(couch ssp)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif(WIN32)

install(TARGETS couch couchlib couchlua)
