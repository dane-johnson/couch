#include "Shader.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
  std::string vertexCode;
  std::string fragmentCode;

  std::ifstream vShaderFile;
  std::ifstream fShaderFile;

  vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  try {
    vShaderFile.open(vertexPath);
    fShaderFile.open(fragmentPath);
    std::stringstream vShaderStream, fShaderStream;

    vShaderStream << vShaderFile.rdbuf();
    fShaderStream << fShaderFile.rdbuf();

    vShaderFile.close();
    fShaderFile.close();

    vertexCode = vShaderStream.str();
    fragmentCode = fShaderStream.str();
  } catch (std::ifstream::failure e) {
    std::cerr << "Error reading shader file." << std::endl;
  }

  const char * vShaderCode = vertexCode.c_str();
  const char * fShaderCode = fragmentCode.c_str();
  

  Id vertex, fragment;
  int success;
  char infoLog[512];

  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vShaderCode, NULL);
  glCompileShader(vertex);
  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, infoLog);
    std::cerr << "Vertex shader failed compilation\n" << infoLog << std::endl;
  }
  
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fShaderCode, NULL);
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

void Shader::UpdateColor(bool usesColor) {
  glUniform1i(glGetUniformLocation(id, "material.usesColor"), (int) usesColor);
}

void Shader::UpdateColor(bool usesColor, Color color) {
  glUniform1i(glGetUniformLocation(id, "material.usesColor"), (int) usesColor);
  glUniform3f(glGetUniformLocation(id, "material.color"), color.r, color.g, color.b);
}

void Shader::UpdateTex(bool usesTex) {
  glUniform1i(glGetUniformLocation(id, "material.usesTex"), (int) usesTex);
}
void Shader::UpdateTex(bool usesTex, Texture tex) {
  glUniform1i(glGetUniformLocation(id, "material.usesTex"), (int) usesTex);
  glBindTexture(GL_TEXTURE_2D, tex.id);
}

Name Shader::GetName() const {
  return "Unnamed Shader";
}
