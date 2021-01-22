#include "Shader.h"

Shader::Shader(const char* vertexCode, const char* fragmentCode) {
  Id vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertexCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cerr << "Vertex shader failed compilation\n" << infoLog << std::endl;
  }
  
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragmentCode, NULL);
  glCompileShader(fragment);
  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, infoLog);
    std::cerr << "Fragment shader failed compilation\n" << infoLog << std::endl;
  }

  id = glCreateProgram();
  glAttachShader(id, vertex);
  glAttachShader(id, fragment);
  glLinkProgram(id);
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if(!success) {
    glGetProgramInfoLog(id, 512, NULL, infoLog);
        std::cerr << "Shader program linking failed\n" << infoLog << std::endl;
  }

  glDeleteShader(vertex);
  glDeleteShader(fragment);
}

void Shader::Use() {
  glUseProgram(id);
}

void Shader::UpdateView(Matrix view) {
  glUniformMatrix4fv(glGetUniformLocation(id, "VIEW"), 1, GL_FALSE, glm::value_ptr(view));
}

void Shader::UpdateModel(Matrix model) {
  glUniformMatrix4fv(glGetUniformLocation(id, "MODEL"), 1, GL_FALSE, glm::value_ptr(model));
}

void Shader::UpdateProjection(Matrix projection) {
  glUniformMatrix4fv(glGetUniformLocation(id, "PROJECTION"), 1, GL_FALSE, glm::value_ptr(projection));
}

void Shader::UpdateMaterial(Material material) {
  glUniform1i(glGetUniformLocation(id, "material.usesColor"), (int) material.usesColor);
  glUniform3f(glGetUniformLocation(id, "material.color"),
	      material.color.r,
	      material.color.g,
	      material.color.b);
  glUniform1i(glGetUniformLocation(id, "material.usesTex"), (int) material.usesTex);
  if (material.usesTex) {
    glBindTexture(GL_TEXTURE_2D, material.tex.id);
  }
  glUniform1f(glGetUniformLocation(id, "material.alphaScissor"), material.alphaScissor);
  glUniform1i(glGetUniformLocation(id, "material.unshaded"), (int) material.unshaded);
  glUniform1i(glGetUniformLocation(id, "material.cullBack"), (int) material.cullBack);
}

void Shader::UpdateDirectionalLight(DirectionalLight directionalLight) {
  glUniform3fv(glGetUniformLocation(id, "directionalLight.direction"), 1, glm::value_ptr(directionalLight.direction));
  glUniform3fv(glGetUniformLocation(id, "directionalLight.color"), 1, glm::value_ptr(directionalLight.color));

  glUniform1f(glGetUniformLocation(id, "directionalLight.ambient"), directionalLight.ambient);
  glUniform1f(glGetUniformLocation(id, "directionalLight.diffuse"), directionalLight.diffuse);
  glUniform1f(glGetUniformLocation(id, "directionalLight.specular"), directionalLight.specular);
}

Name Shader::GetName() const {
  return "Unnamed Shader";
}
