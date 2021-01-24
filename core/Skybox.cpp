#include "Skybox.h"

cfloat vertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};

Skybox::Skybox() {
  glGenVertexArrays(1, &cube);
  glBindVertexArray(cube);

  Id vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // We're just going to use position data
  // UV data is the same
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * (sizeof(cfloat)), (void*) 0);
  glBindVertexArray(0);
}

Name Skybox::GetType() const { return "Skybox"; }

Skybox *Skybox::Create() {
  return new Skybox;
}

Skybox *Skybox::Duplicate() {
  Skybox* skybox = static_cast<Skybox*>(Node::Duplicate());
  skybox->id = id;
  skybox->cube = cube;

  return skybox;
}

Skybox *Skybox::Instance() {
  return static_cast<Skybox*>(Node::Instance());
}

Skybox *Skybox::FromFiles(const char *right, const char* left, const char* top, const char* bottom, const char* front, const char* back) {
  // HOCUS: https://learnopengl.com/Advanced-OpenGL/Cubemaps
  Skybox *sb = new Skybox();
  glGenTextures(1, &sb->id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, sb->id);

  int width, height, nrChannels;
  unsigned char* data;
  const char* files[] = {right, left, top, bottom, front, back};
  for (int i = 0; i < 6; i++) {
    data = stbi_load(files[i], &width, &height, &nrChannels, 3);
    if (!data) {
      Util::Die("Could not load skybox image ", files[i]);
    }
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
		 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return sb;
}

void Skybox::DrawSkybox() {
  glBindVertexArray(cube);
  glDrawArrays(GL_TRIANGLES, 0, 36);
  glBindVertexArray(0);
}
