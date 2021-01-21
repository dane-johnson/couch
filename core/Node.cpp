#include "Node.h"

Name Node::GetType() const {return "Node";}

Node *Node::root = {new Node()};
Node *Node::GetRoot() {
  return root;
}
bool Node::IsDrawable() const {
  return false;
}
bool Node::IsTransformable() const {
  return false;
}

void NodeList::Append(Node *node) {
  push_back(node);
}
