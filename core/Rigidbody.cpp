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
 
  Defines physics bodies and their interfaces with the physics engine
*/
#include "Rigidbody.h"
#include "World.h"

Rigidbody::Rigidbody() {
  collisionShape = new btSphereShape(1.0f);
}

Rigidbody *Rigidbody::Create() {
  return new Rigidbody;
}

Rigidbody *Rigidbody::Duplicate() {
  Rigidbody *rigidbody = static_cast<Rigidbody*>(Spatial::Duplicate());

  rigidbody->collisionShape = collisionShape;
  rigidbody->btBody = btBody;
  rigidbody->mass = mass;
  return rigidbody;
}

Rigidbody *Rigidbody::Instance() {
  Rigidbody *rigidbody = static_cast<Rigidbody*>(Node::Instance());

  rigidbody->collisionShape = collisionShape;
  rigidbody->btBody = new btRigidBody(rigidbody->mass, new RigidbodyMotionState(rigidbody), rigidbody->collisionShape);
  rigidbody->btBody->setAngularFactor(character ? 0.0f : 1.0f);

  World *world = World::GetWorld();
  world->AddRigidbody(rigidbody);

  return rigidbody;
}

void Rigidbody::Translate(Vector3 offset) {
  Spatial::Translate(offset);
  if (not IsPrefab()) {
    btBody->translate(btVector3(offset.x,
				offset.y,
				offset.z));
  }
}

void Rigidbody::SetCollisionShape(CollisionShape collisionShape) {
  if (this->collisionShape) {
    delete this->collisionShape;
  }
  this->collisionShape = collisionShape.shape;
}

float Rigidbody::GetMass() {
  return mass;
}

void Rigidbody::SetMass(float mass) {
  this->mass = mass;
  if (not IsPrefab()) {
    btBody->setMassProps(mass, btVector3(0, 0, 0));
  }
}

void Rigidbody::ApplyImpulse(Vector3 impulse) {
  btBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
}

void Rigidbody::ApplyForce(Vector3 force) {
  btBody->applyCentralForce(btVector3(force.x, force.y, force.z));
}


bool Rigidbody::GetCharacter() {
  return character;
}

void Rigidbody::SetCharacter(bool character) {
  this->character = character;
}


RigidbodyMotionState::RigidbodyMotionState(Rigidbody *rigidbody) {
  this->rigidbody = rigidbody;
}

void RigidbodyMotionState::getWorldTransform(btTransform &worldTrans) const {
  Transform transform = rigidbody->GetTransform();
  worldTrans.setOrigin(btVector3(
			 transform.position.x,
			 transform.position.y,
			 transform.position.z));
  btQuaternion quat;
  quat.setEuler(transform.rotation.z,
		transform.rotation.y,
		transform.rotation.x);
  worldTrans.setRotation(quat);
}

void RigidbodyMotionState::setWorldTransform(const btTransform &worldTrans) {
  Transform transform = rigidbody->GetTransform();
  transform.position = Vector3(worldTrans.getOrigin().getX(),
					  worldTrans.getOrigin().getY(),
					  worldTrans.getOrigin().getZ());
  
  worldTrans.getRotation().getEulerZYX(transform.rotation.z,
				       transform.rotation.y,
				       transform.rotation.x);
  rigidbody->SetTransform(transform);
}
