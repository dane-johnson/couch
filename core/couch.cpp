// C++ includes
#include <iostream>

// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

#include "Shaders/FlatShader.h"
#include "Ball.h"
#include "Camera.h"
#include "Input.h"
#include "Node.h"
#include "Lua.h"

Window *window;

const int width = 800;
const int height = 600;

Node *root;

void render(Node *curr, Shader *shader, Matrix model) {
  if (curr->IsDrawable()) {
    if (curr->IsTransformable()) {
      Spatial *spatial = dynamic_cast<Spatial*>(curr);
      model = glm::rotate(model, spatial->transform.rotation.x, Vector3(1.0f, 0.0f, 0.0f));
      model = glm::rotate(model, spatial->transform.rotation.y, Vector3(0.0f, 1.0f, 0.0f));
      model = glm::rotate(model, spatial->transform.rotation.z, Vector3(0.0f, 0.0f, 1.0f));
      model = glm::translate(model, spatial->transform.position);
      shader->UpdateModel(model);
    }
    Drawable *drawable = dynamic_cast<Drawable*>(curr);
    drawable->Draw();
  }
  for (Node *child : curr->children) {
    render(child, shader, model);   
  }
}


int main() {

  int err;
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
  glfwWindowHintString(GLFW_X11_CLASS_NAME, "Couch");

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

  root = Node::GetRoot();

  Input *input = Input::GetInstance();
  input->Use(window);

  Camera defaultCamera;
  
  FlatShader *shader = new FlatShader();
  shader->Use();
  shader->UpdateColor(Vector3(0.0f, 1.0f, 0.0f));
  
  Matrix projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);
  shader->UpdateProjection(projection);

  // TODO Allow multiple scripting languages
  Lua *lua = new Lua();
  lua->Initialize();

  double lastTime = glfwGetTime();
  double delta = 0.0;

  while(!glfwWindowShouldClose(window)) {
    glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    lua->Update(delta);

    Matrix view(1.0f);
    Camera *camera = Camera::GetCurrentCamera();
    view = glm::rotate(view, -camera->transform.rotation.x, Vector3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, -camera->transform.rotation.y, Vector3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, -camera->transform.rotation.z, Vector3(0.0f, 0.0f, 1.0f));
    view = glm::translate(view, -camera->transform.position);
    shader->UpdateView(view);

    // Render the scene tree
    render(root, shader, Matrix(1.0f));
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    double curTime = glfwGetTime();
    delta = curTime - lastTime;
    lastTime = curTime;
  }

  lua->Close();
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
