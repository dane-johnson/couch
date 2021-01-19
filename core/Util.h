#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <stdlib.h>

namespace Util {
  void Die(const char *msg);
  void Die(const char * msg, const char * more);
  void Die(std::string msg);
}

#endif /* UTIL_H */
