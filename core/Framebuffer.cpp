/*
  Dane Johnson <dane@danejohnson.org>
 
  LICENSE
 
  Couch  Copyright (C) 2021 Dane Johnson

  This program comes with ABSOLUTELY NO WARRANTY; without event the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for details at
  https://www.gnu.org/licenses/gpl-3.0.html
  
  This is free software, and you are welcome to redistribute it
  under the terms of the GNU General Public License as published
  by the Free Software Foundation; either version 3 of the License,
  or (at your option) any later version.
 
  DESCRIPTION
   
  Framebuffers are essentially just things that can be drawn to. They have
  a number of settings that are set via stateful calls to OpenGL, so they
  are wrapped here so they can be saved and restored in a stateless fashion.
*/

#include "Framebuffer.h"

Framebuffer::Framebuffer() {
  glGenFramebuffers(1, &fbo);
}

Framebuffer::Framebuffer(Id fbo) {
  this->fbo = fbo;
}

Framebuffer::~Framebuffer() {
  // If this isn't the default framebuffer.
  if (fbo != 0) {
    glDeleteFramebuffers(1, &fbo);
  }
}

void Framebuffer::Enable() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
  if (depthTest) {
    glEnable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_DEPTH_TEST);
  }
}


void Framebuffer::Clear() {
  glClearColor(clearColor.x, clearColor.y, clearColor.z, 1.0f);
  glClear(clearFlags);
}

void Framebuffer::Bind() {
  glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// Gotta initialize static members here so DLLs will
// only create one instance.
static FramebufferStack static_stack;

void FramebufferStack::Save(Framebuffer *buffer) {
  stack.push_back(curr);
  curr = buffer;
}

void FramebufferStack::Restore() {
  curr = stack.back();
  stack.pop_back();

  curr->Enable();
}

FramebufferStack *FramebufferStack::GetStack() {
  return &static_stack;
}
