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
 
   Node is the parent class for all classes that would be in the scene
   tree. The root of the scene tree is always a node.
*/

#include "Node.h"
#include "Util.h"

void NodeList::Append(Node *node) {
  if (this->isPrefabList and not node->isPrefab) {
    Util::Die("Attempt to add instanced node to prefab list!");
  }
  if (node->isPrefab and not this->isPrefabList) {
    Util::Die("Attempt to add prefab node to instanced list!");
  }
  push_back(node);
}

bool NodeList::IsPrefabList() {
  return isPrefabList;
}

Name Node::GetType() const {return "Node";}

bool Node::IsPrefab() {
  return isPrefab;
}

NodeList Node::GetChildren() {
  return children;
}

void Node::AddChild(Node *child) {
  children.Append(child);
}

Node *Node::GetRoot() {
  return root;
}

Node* Node::Create() {
  return new Node;
}

Node* Node::Duplicate() {
  return Create();
}

Node* Node::Instance() {
  if (not isPrefab) {
    Util::Die("Attempt to instance an instanced node!");
  }
  Node* instance = Duplicate();
  instance->isPrefab = false;
  instance->children.isPrefabList = false;
  // Instance the children to the instanced list
  for (Node *child : children) {
    instance->children.Append(child->Instance());
  }

  return instance;
}

Node *Node::root = {Node().Instance()};
