/**
   @file
   @author Dane Johnson <dane@danejohnson.org>
 
   @section LICENSE
 
   Couch  Copyright (C) 2021 Dane Johnson

   This program comes with ABSOLUTELY NO WARRANTY; without event the
   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
   See the GNU General Public License for details at
   https://www.gnu.org/licenses/gpl-3.0.html
  
   This is free software, and you are welcome to redistribute it
   under the terms of the GNU General Public License as published
   by the Free Software Foundation; either version 3 of the License,
   or (at your option) any later version.
 
   @section DESCRIPTION
   
   Framebuffers are essentially just things that can be drawn to. They have
   a number of settings that are set via stateful calls to OpenGL, so they
   are wrapped here so they can be saved and restored in a stateless fashion.
*/

#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <vector>

#include "types.h"

class Framebuffer {
public:
  Framebuffer();
  /**
     If the frame buffer has already been initialized, you can pass it
     in with this constructor
     @param fbo the frame buffer object handle.
  */
  Framebuffer(Id fbo);
  /** 
      Apply the configuration for this framebuffer to the OpenGL state.
  */
  ~Framebuffer();
  void Enable();
  /** 
      Clear out this framebuffer.
  */
  void Clear();
  /**
     Bind the texture without applying configuration.
  */
  void Bind();
  /**
     What clear color to draw to this frame buffer
  */  
  Vector3 clearColor = Vector3(0.0f, 0.0f, 1.0f);
  /**
     What bit(s) to clear in this buffer.
  */
  int clearFlags = GL_COLOR_BUFFER_BIT;
  /**
     Should we enable depth testing?
  */
  bool depthTest = false;
private:
  Id fbo;
};

class FramebufferStack {
public:
  void Save(Framebuffer *buffer);
  void Restore();
  Framebuffer *curr = new Framebuffer(0);  // Start with the default framebuffer
  static FramebufferStack *GetStack();
private:
  std::vector<Framebuffer *> stack;
};

#endif /* FRAMEBUFFER_H */
