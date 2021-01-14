// C++ includes
#include <iostream>

#ifdef LUA_SCRIPTING
// Lua includes
extern "C" {
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>  
}
#endif // LUA_SCRIPTING

// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

#include "Shader.h"
#include "Ball.h"
#include "Camera.h"
#include "Input.h"

Window *window;

const int width = 800;
const int height = 600;

MeshList meshes;

void AddMeshToList(Mesh &mesh) {
  meshes.push_front(&mesh);
}
#ifdef LUA_SCRIPTING

extern "C" int luaopen_couch(lua_State* L);

#endif // LUA_SCRIPTING


int main() {

  int err;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(width, height, "Couch", NULL, NULL);

  if (!window) {
    std::cerr << "Error creating window" << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);

  err = glewInit();
  if (err != GLEW_OK) {
    std::cerr << "Error initializing glew" << std::endl;
  }

  glViewport(0, 0, width, height);

#ifdef LUA_SCRIPTING
  lua_State *L;
  L = luaL_newstate();
  luaopen_base(L);
  luaopen_couch(L);
  if (luaL_loadfile(L, "main.lua") == 0){
    lua_call(L, 0, 0);
    lua_getglobal(L, "init");
    lua_call(L, 0, 0);
  } else {
    std::cerr << "Could not find main.lua" << std::endl;
    return 1;
  }
  glfwSetWindowUserPointer(window, (void*) L);
#endif // LUA_SCRIPTING

  Input *input = Input::GetInstance();
  input->Use(window);

  Camera defaultCamera;
  
  Shader shader("shaders/flat.vert", "shaders/flat.frag");
  shader.Use();
  
  Matrix projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
  shader.UpdateProjection(projection);

  double lastTime = glfwGetTime();
  double delta = 0.0;

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    Matrix view(1.0f);
    Camera *camera = Camera::GetCurrentCamera();
    view = glm::translate(view, -camera->transform.position);
    shader.UpdateView(view);


#ifdef LUA_SCRIPTING
    lua_getglobal(L, "update");
    lua_pushnumber(L, delta);
    lua_call(L, 1, 0);
#endif // LUA_SCRIPTING

    for (Mesh *mesh : meshes) {
      Matrix model(1.0f);
      model = glm::translate(model, mesh->transform.position);
      shader.UpdateModel(model);
      mesh->Draw();
    }

    
    glfwSwapBuffers(window);
    glfwPollEvents();

    double curTime = glfwGetTime();
    delta = curTime - lastTime;
    lastTime = curTime;
  }

#ifdef LUA_SCRIPTING

  lua_close(L);

#endif // LUA_SCRIPTING
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
