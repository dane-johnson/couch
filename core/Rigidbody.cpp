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

void Rigidbody::SetCollisionShape(CollisionShape collisionShape) {
  if (this->collisionShape) {
    delete this->collisionShape;
  }
  this->collisionShape = collisionShape.shape;
}

void Rigidbody::ApplyImpulse(Vector3 impulse) {
  btBody->applyCentralImpulse(btVector3(impulse.x, impulse.y, impulse.z));
}

void Rigidbody::ApplyForce(Vector3 force) {
  btBody->applyCentralForce(btVector3(force.x, force.y, force.z));
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
