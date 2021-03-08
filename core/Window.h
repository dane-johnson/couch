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
   
   The window controls interfacing with the operating system and creating the 
   interface.
*/
#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window {
public:
  /**
     Initializes the window.
  */
  void Init();
  /**
     @returns whether or not the user tried to close the window
  */
  bool ShouldClose();
  /**
     Begin rendering to the window
   */
  void Enable();
  /**
     Swap the buffers and poll for events
  */
  void Update();
  /**
     Close the window.
  */
  void Close();
private:
  friend class Input;
  GLFWwindow *glfwWindow;
};

#endif /* WINDOW_H */
