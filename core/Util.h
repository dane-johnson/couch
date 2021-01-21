#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <stdlib.h>

#include "types.h"
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
  
    for (Node *child : root->children) {
      T* res = FindNodeByType<T>(child, type);
      if (res) {
	return res;
      }
    }
    return nullptr;
  }
}

#endif /* UTIL_H */
