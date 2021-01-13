#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

#include "Shader.h"
#include "Ball.h"

Window *window;

const int width = 800;
const int height = 600;

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

  Shader shader("shaders/flat.vert", "shaders/flat.frag");
  shader.Use();
  
  Ball ball;
  ball.SetupMesh();

  Matrix projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
  shader.UpdateProjection(projection);
  Matrix view(1.0f);
  shader.UpdateView(view);

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    Matrix model(1.0f);
    model = glm::translate(model, ball.transform.position);
    shader.UpdateModel(model);
    ball.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
