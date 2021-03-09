#include "Screen.h"

const Vertex vertices[] = {
  Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
  Vertex(-1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
  Vertex(1.0f, -1.0f, 0.0f, 1.0f, 0.0f),

  Vertex(-1.0f, 1.0f, 0.0f, 0.0f, 1.0f),
  Vertex(1.0f, -1.0f, 0.0f, 1.0f, 0.0f),
  Vertex(1.0f, 1.0f, 0.0f, 1.0f, 1.0f)
};

Screen::Screen() {
  // Setup quad
  glGenVertexArrays(1, &quad);
  glBindVertexArray(quad);
  
  Id vbo;
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // Vertex positions
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) 0);
  // Vertex Normals
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (3 * sizeof(float)));
  //Vertex UV
  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) (6 * sizeof(float)));

  glBindVertexArray(0);

  // Setup frame buffers
  framebuffer.clearColor = Vector3(1.0f, 0.0f, 0.0f);
  framebuffer.clearFlags = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
  framebuffer.depthTest = true;
  framebuffer.Bind();

  tex.width = width;
  tex.height = height;
  glGenTextures(1, &tex.id);
  glBindTexture(GL_TEXTURE_2D, tex.id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glBindTexture(GL_TEXTURE_2D, 0);

  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex.id, 0);

  // Setup render buffer
  glGenRenderbuffers(1, &renderbuffer);
  glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
  glBindRenderbuffer(GL_RENDERBUFFER, 0);

  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderbuffer);

  if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
    std::cerr << "Error setting up screen framebuffer." << std::endl;
    exit(1);
  }
  FramebufferStack::GetStack()->curr->Bind();
}

void Screen::Enable() {
  FramebufferStack::GetStack()->Save(&framebuffer);
  framebuffer.Enable();
  framebuffer.Clear();
}

void Screen::Disable() {
  FramebufferStack::GetStack()->Restore();
}

void Screen::Draw() {
  glBindVertexArray(quad);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}
