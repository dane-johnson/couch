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
 
   A spatial is a node with a transform property, i.e. position, scale or rotation.
   They can be instanced on the scene tree as an anchor for some other nodes.
*/
#include "Spatial.h"

Name Spatial::GetType() const {return "Spatial";}

Transform Spatial::GetTransform() {
  return transform;
}

void Spatial::SetTransform(Transform transform) {
  this->transform = transform;
}

Spatial *Spatial::Create() {
  return new Spatial;
}

void Spatial::Translate(Vector3 offset) {
  Transform t = this->GetTransform();
  t.position += offset;
  this->SetTransform(t);
}

void Spatial::RotateX(float phi) {
  Transform t = this->GetTransform();
  t.rotation.x += phi;
  this->SetTransform(t);
}

void Spatial::RotateY(float phi) {
  Transform t = this->GetTransform();
  t.rotation.y += phi;
  this->SetTransform(t);
}

void Spatial::RotateZ(float phi) {
  Transform t = this->GetTransform();
  t.rotation.z += phi;
  this->SetTransform(t);
}

void Spatial::UniformScale(float scale) {
  Transform t = this->GetTransform();
  t.scale *= scale;
  this->SetTransform(t);
}

Spatial *Spatial::Duplicate() {
  Spatial *spatial = static_cast<Spatial*>(Node::Duplicate());
  spatial->transform = transform;

  return spatial;
}

Spatial *Spatial::Instance() {
  return static_cast<Spatial*>(Node::Instance());
}

