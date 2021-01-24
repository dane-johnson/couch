#include "Node.h"
#include "Util.h"

Name Node::GetType() const {return "Node";}

Node *Node::root = {Node().Instance()};
Node *Node::GetRoot() {
  return root;
}
bool Node::IsDrawable() const {
  return false;
}
bool Node::IsTransformable() const {
  return false;
}

Node* Node::Create() {
  return new Node;
}

Node* Node::Duplicate() {
  return Create();
}

Node* Node::Instance() {
  if (not this->isPrefab) {
    Util::Die("Attempt to instance an instanced node!");
  }
  Node* instance = Duplicate();
  instance->isPrefab = false;
  instance->children = NodeList();
  instance->children.isPrefabList = false;
  for (Node *child : children) {
    instance->children.Append(child->Instance());
  }

  return instance;
}

void NodeList::Append(Node *node) {
  if (this->isPrefabList and not node->isPrefab) {
    Util::Die("Attempt to add instanced node to prefab list!");
  }
  if (node->isPrefab and not this->isPrefabList) {
    Util::Die("Attempt to add prefab node to instanced list!");
  }
  push_back(node);
}
