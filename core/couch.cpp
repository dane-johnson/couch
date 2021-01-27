// C++ includes
#include <iostream>

// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "types.h"

#include "Util.h"

#include "Shaders/FlatShader.h"
#include "Shaders/ScreenShader.h"
#include "Shaders/SkyboxShader.h"

#include "Screen.h"

#include "Camera.h"
#include "Input.h"
#include "Node.h"
#include "Mesh.h"
#include "Light.h"
#include "Skybox.h"

#include "Rigidbody.h"
#include "World.h"


#include "Scripting/Lua.h"

// Thirdparty Includes
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Window *window;

const int width = 800;
const int height = 600;

Node *root;

void render(Node *curr, Shader *shader, Matrix model) {
  Spatial *spatial = dynamic_cast<Spatial*>(curr);
  if (spatial) {
    Transform transform = spatial->GetTransform();
    model = glm::rotate(model, transform.rotation.x, Vector3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, transform.rotation.y, Vector3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, transform.rotation.z, Vector3(0.0f, 0.0f, 1.0f));
    model = glm::translate(model, transform.position);
    model = glm::scale(model, transform.scale);
    shader->UpdateModel(model);
    shader->UpdateNormal(glm::mat3(glm::transpose(glm::inverse(model))));
  }

  Mesh *mesh = dynamic_cast<Mesh*>(curr);
  if (mesh) {
    mesh->Draw(shader);
  }
  for (Node *child : curr->GetChildren()) {
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

  World *world = World::GetWorld();

  Screen screen;
  ScreenShader *screenShader = new ScreenShader();

  SkyboxShader *skyboxShader = new SkyboxShader();
  
  FlatShader *shader = new FlatShader();
  
  Matrix projection = glm::perspective(glm::radians(45.0f), 800.0f/600.0f, 0.1f, 100.0f);

  // TODO Allow multiple scripting languages
  Lua *lua = new Lua();
  lua->Initialize();

  double lastTime = glfwGetTime();
  double delta = 0.0;

  while(!glfwWindowShouldClose(window)) {

    // Physics update()
    world->Step(delta);
    
    // Start rendering to texture;
    screen.Enable();

    lua->Update(delta);

    shader->Use();
    shader->UpdateProjection(projection);
    Matrix view(1.0f);
    Camera *camera = Camera::GetCurrentCamera();
    Transform camera_transform = camera->GetTransform();
    view = glm::rotate(view, -camera_transform.rotation.x, Vector3(1.0f, 0.0f, 0.0f));
    view = glm::rotate(view, -camera_transform.rotation.y, Vector3(0.0f, 1.0f, 0.0f));
    view = glm::rotate(view, -camera_transform.rotation.z, Vector3(0.0f, 0.0f, 1.0f));
    view = glm::translate(view, -camera_transform.position);
    shader->UpdateView(view);

    // Find the lights
    DirectionalLight *dirLight = Util::FindNodeByType<DirectionalLight>(root, "DirectionalLight");
    if (dirLight) {
      shader->UpdateDirectionalLight(*dirLight);
    } else {
      // No light in scene
      shader->UpdateDirectionalLight(DirectionalLight());
    }

    // Render the scene tree
    render(root, shader, Matrix(1.0f));

    // Render the skybox
    Skybox *skybox = Util::FindNodeByType<Skybox>(root, "Skybox");
    if (skybox) {
      glDepthFunc(GL_LEQUAL);
      skyboxShader->Use();
      skyboxShader->UpdateView(glm::mat4(glm::mat3(view)));
      skyboxShader->UpdateProjection(projection);
      skyboxShader->UpdateSkybox(*skybox);
      skybox->DrawSkybox();
      glDepthFunc(GL_LESS);
    }

    // Stop rendering to texture
    screen.Disable();
    // // Render the screen
    screenShader->Use();
    screenShader->UpdateTex(screen.tex);
    glViewport(0, 0, width, height);
    screen.Draw();
    
    glfwSwapBuffers(window);
    glfwPollEvents();

    double curTime = glfwGetTime();
    delta = curTime - lastTime;
    lastTime = curTime;
  }

  delete screenShader;
  delete skyboxShader;
  delete flatShader()
  lua->Close();
  delete lua;
  
  glfwDestroyWindow(window);
  glfwTerminate();
  return 0;
}
