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
   
   Lights provide lighting to a scene. They can be colored and support
   ambient, diffuse, and specular properties.
*/
#ifndef LIGHT_H
#define LIGHT_H

#include "types.h"
#include "Spatial.h"

class Light : public Spatial {
public:
  Vector3 color;
  float ambient, diffuse, specular;
  virtual Name GetType() const;
  virtual Light *Create();
  virtual Light *Duplicate();
  virtual Light *Instance();
};

class DirectionalLight : public Light {
public:
  Vector3 direction;
  DirectionalLight();
  DirectionalLight(Vector3 direction, Vector3 color, float ambient, float diffuse, float specular);
  virtual Name GetType() const;
  virtual DirectionalLight *Create();
  virtual DirectionalLight *Duplicate();
  virtual DirectionalLight *Instance();
};

#endif /* LIGHT_H */
