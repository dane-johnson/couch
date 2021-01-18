#ifndef NODE_H
#define NODE_H

#include <vector>

class Node; // Forwards declare
class NodeList : public std::vector<Node*> {
public:
  void Append(Node *node);
};

class Node {
public:
  NodeList children;
  static Node *GetRoot();
  virtual bool IsDrawable() const;
  virtual void Draw(){};
  virtual bool IsTransformable() const;
private:
  static Node *root;
};

#endif /* NODE_H */
