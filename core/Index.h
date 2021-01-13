#ifndef INDEX_H
#define INDEX_H

#include <vector>

struct Index {
  unsigned int v0, v1, v2;
  Index(unsigned int v0, unsigned int v1, unsigned int v2);
};

typedef std::vector<Index> IndexList;

#endif /* INDEX_H */
