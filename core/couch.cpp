// C includes
#include <unistd.h>

// C++ includes
#include <iostream>

// OpenGL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "types.h"
#include "Window.h"

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
#include "Scripting/Guile.h"

Node *root;

char script_type = 'l';
ScriptingLanguage *sl;

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

void parse_args(int argc, char* argv[]) {
  int curr = 1;
  while (curr < argc) {
    if (argv[curr][0] == '-') {
      switch(argv[curr][1]) {
      case 'l':
	++curr;
	script_type = argv[curr][0];
	++curr;
	break;
      }
    } else {
      chdir(argv[curr]);
      ++curr;
    }
  }
}

int main(int argc, char *argv[]) {

  parse_args(argc, argv);
  
  Window window;
  window.Init();
  
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

  switch(script_type) {
  case 'l':
    sl = new Lua();
    break;
  case 'g':
    sl = new Guile();
    break;
  }
  sl->Initialize();


  double lastTime = glfwGetTime();
  double delta = 0.0;

  while(!window.ShouldClose()) {
    // Physics update
    world->Step(delta);

    // Script update
    ScriptingLanguage::GetCurrentLanguage()->Update(delta);
    
    // Delete freed nodes
    root->DoFree();

    // Start rendering to screen
    screen.Enable();

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

    PointLightList pointLights = Util::FindNodesByType<PointLight>(root, "PointLight");
    shader->UpdatePointLights(pointLights);

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

    screenShader->Use();
    screenShader->UpdateTex(screen.tex);
    
    screen.Draw();

    window.Update();

    double curTime = glfwGetTime();
    delta = curTime - lastTime;
    lastTime = curTime;
  }
  
  ScriptingLanguage::GetCurrentLanguage()->Close();
  window.Close();
  return 0;
}
