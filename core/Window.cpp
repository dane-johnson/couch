#include "Window.h"

const int width = 800;
const int height = 600;

void Window::Init() {
  int err;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHintString(GLFW_X11_CLASS_NAME, "Couch");

  glfwWindow = glfwCreateWindow(width, height, "Couch", NULL, NULL);

  if (!glfwWindow) {
    throw "Error creating window.";
  }

  glfwMakeContextCurrent(glfwWindow);

  err = glewInit();
  if (err != GLEW_OK) {
    throw "Error initiailizing GLEW.";
  }

  glViewport(0, 0, width, height);
}

bool Window::ShouldClose() {
  return glfwWindowShouldClose(glfwWindow);
}

void Window::Update() {
  glfwSwapBuffers(glfwWindow);
  glfwPollEvents();
}

void Window::Close() {
  glfwDestroyWindow(glfwWindow);
  glfwTerminate();
}
