#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "types.h"
class Node;
#include "Node.h"

namespace Util {
  void Die(const char *msg);
  void Die(const char * msg, const char * more);
  void Die(std::string msg);

  template<class T>
  T* FindNodeByType(Node *&root, const Name &type) {
    if (root->GetType() == type) {
      return dynamic_cast<T*>(root);
    }
  
    for (Node *child : root->GetChildren()) {
      T* res = FindNodeByType<T>(child, type);
      if (res) {
	return res;
      }
    }
    return nullptr;
  }
  template<class T>
  std::vector<T*> FindNodesByType(Node *&root, const Name &type) {
    std::vector<T*> nodes;
    if (root->GetType() == type) {
      nodes.push_back(dynamic_cast<T*>(root));
    }
    for (Node *child : root->GetChildren()) {
      std::vector<T*> childs = FindNodesByType<T>(child, type);
      nodes.insert(nodes.begin(), childs.begin(), childs.end());
    }
    return nodes;
  }

  std::string ShaderArrayName(const char* arrName, int index, const char* memberName);
}

#endif /* UTIL_H */
