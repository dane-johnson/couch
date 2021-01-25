#include "Rigidbody.h"
#include "World.h"

Rigidbody::Rigidbody() {}

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

  rigidbody->collisionShape = new btSphereShape(1.0f);
  rigidbody->btBody = new btRigidBody(rigidbody->mass, new RigidbodyMotionState(rigidbody), rigidbody->collisionShape);
  assert(rigidbody);

  World *world = World::GetWorld();
  world->AddRigidbody(rigidbody);

  return rigidbody;
}

RigidbodyMotionState::RigidbodyMotionState(Rigidbody *rigidbody) {
  this->rigidbody = rigidbody;
}

void RigidbodyMotionState::getWorldTransform(btTransform &worldTrans) const {
  worldTrans.setOrigin(btVector3(
			 rigidbody->transform.position.x,
			 rigidbody->transform.position.y,
			 rigidbody->transform.position.z));
  btQuaternion quat;
  quat.setEuler(rigidbody->transform.rotation.z,
		rigidbody->transform.rotation.y,
		rigidbody->transform.rotation.x);
  worldTrans.setRotation(quat);
}

void RigidbodyMotionState::setWorldTransform(const btTransform &worldTrans) {
  rigidbody->transform.position = Vector3(worldTrans.getOrigin().getX(),
					  worldTrans.getOrigin().getY(),
					  worldTrans.getOrigin().getZ());
  
  worldTrans.getRotation().getEulerZYX(rigidbody->transform.rotation.z,
				       rigidbody->transform.rotation.y,
				       rigidbody->transform.rotation.x);
}
