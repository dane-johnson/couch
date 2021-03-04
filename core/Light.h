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

#include <vector>

#include "types.h"
#include "Spatial.h"

/**
   All lights have color as well as ambient, diffuse, and specular properties.
   In the future, light properties might be a color, but for now they are
   strength modulations on the main light color.
*/
class Light : public Spatial {
public:

  /**
     Get the color property of this light
     @returns The color property
  */
  Vector3 GetColor();
  /**
    Set the color property of this light
    @param color The desired color.
  */
  void SetColor(Vector3 color);

  /** Ambient light is how much light is emitted from an object illuminated by
      this light with no accounting for incidence angle or the location of the observer.
      @returns The ambient intensity
  */
  float GetAmbient();
  /** Set the ambient light intensity.
      @param ambient The desired ambient intensity for this light.
  */
  void SetAmbient(float ambient);

  /** Diffuse light is how much light is reflected by an object illuminated
      by this light, accounting for incidence angle of the light but not the
      location of the observer.
      @returns The diffuse intensity.
  */
  float GetDiffuse();
  /** Set the diffuse intensity.
      @param diffuse The desired diffuse intensity for this light
  */
  void SetDiffuse(float diffuse);

  /** Specular light is how much light is reflected by an object illuminated
      by this light, taking into account both the incidence angle of the light
      as well as the location of the observer. This is what creates the 
      "Specular Artifact", the shiny bit on a 3D sphere.
      @returns The specular intensity
  */
  float GetSpecular();
  /** Set the specular intensity.
      @param specular The desired specular intensity for this light.
  */
  void SetSpecular(float specular);
    
  virtual Light *Create();
  virtual Light *Duplicate();
  virtual Light *Instance();

  virtual Name GetType() const;

protected:
  Vector3 color;
  float ambient, diffuse, specular;
};

/**
   Directional lights are infinitely far away lights that illuminate the whole world.
*/
class DirectionalLight : public Light {
public:
  DirectionalLight();
  DirectionalLight(Vector3 direction, Vector3 color, float ambient, float diffuse, float specular);

  /**
     The direction from which this light is coming.
     @returns The direction of the light.
  */
  Vector3 GetDirection();
  /**
     Set the direction from which the light is coming.
     @param direction The desired light direction
  */
  void SetDirection(Vector3 direction);
  
  virtual Name GetType() const;
  virtual DirectionalLight *Create();
  virtual DirectionalLight *Duplicate();
  virtual DirectionalLight *Instance();
private:
  Vector3 direction;
};

/**
   Point lights are omnidirectional lights that have a limited range.
*/
class PointLight : public Light {
public:
  PointLight();
  PointLight(float radius, Vector3 color, float ambient, float diffuse, float specular);

  /**
     The radius of which the light will shine.
     @returns The light radius.
  */
  float GetRadius();
  /**
     Sets the light radius.
     @param radius The desired radius
  */
  void SetRadius(float radius);
  
  virtual Name GetType() const;
  virtual PointLight *Create();
  virtual PointLight *Duplicate();
  virtual PointLight *Instance();
private:
  float radius;
};

typedef std::vector<PointLight*> PointLightList;

#endif /* LIGHT_H */
