#ifndef NODE_H
#define NODE_H

#include <vector>

#include "types.h"

class Node; // Forwards declare
class NodeList : public std::vector<Node*> {
public:
  void Append(Node *node);
private:
  bool isPrefabList = true;
  friend class Node;
};

class Node {
public:
  NodeList children;
  static Node *GetRoot();
  virtual bool IsDrawable() const;
  virtual void Draw() {};
  virtual bool IsTransformable() const;
  virtual Name GetType() const;
  virtual Node* Create();
  virtual Node* Instance();
  virtual Node* Duplicate();
private:
  static Node *root;
  bool isPrefab = true;
  friend class NodeList;
};

#endif /* NODE_H */
