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
 
   Defines physics bodies and their interfaces with the physics engine
*/
#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <btBulletDynamicsCommon.h>

#include "types.h"
#include "Spatial.h"
#include "CollisionShape.h"

/**
   Rigidbodies are any body that interacts with the physics bodies
*/
class Rigidbody : public Spatial {
public:
  Rigidbody();

  /**
     Directly translate this physics object.
     @param offset The desired translation offset.
  */
  virtual void Translate(Vector3 offset);
    

  /**
     Sets the collision shape of this rigidbody
     @param collisionShape The collision shape
  */
  void SetCollisionShape(CollisionShape collisionShape);
  /**
     Gets the mass of this rigidbody
     @return The mass, 0.0 if this is an infinite mass object
  */
  float GetMass();
  /**
     Sets the mass of this rigidbody.
     Note that setting mass equal to 0.0 will make it an
     infinite mass object
     @param mass The desired mass
  */
  void SetMass(float mass);
  
  /**
     Add an instantaneous impulse to the object.
     Probably shouldn't be called every update.
     @param impulse The impulse vector
  */
  void ApplyImpulse(Vector3 impulse);
  /**
     Add a force to this object, scaled to the time step.
     Can be called every update.
     @param The (unscaled) force
  */
  void ApplyForce(Vector3 force);

  /**
     If this is a character object, meaning it's rotation is not 
     controlled by the physics engine
     @return true if this is a character object
  */
  bool GetCharacter();
  /**
     Sets if this object's rotation is controlled by the physics engine
     @param character true if this is a character object
  */
  void SetCharacter(bool character);

  virtual Rigidbody *Create();
  virtual Rigidbody *Duplicate();
  virtual Rigidbody *Instance();
private:
  bool character = false;
  btRigidBody *btBody;
  btCollisionShape *collisionShape;
  float mass = 1.0f;
  
  friend class World;
};

class RigidbodyMotionState : public btMotionState {
public:
  RigidbodyMotionState(Rigidbody *rigidbody);
  virtual void getWorldTransform(btTransform &worldTrans) const;
  virtual void setWorldTransform(const btTransform &worldTrans);
private:
  Rigidbody *rigidbody;
};

#endif /* RIGIDBODY_H */
