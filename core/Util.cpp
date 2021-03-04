#include "Util.h"

void Util::Die(const char * msg) {
  std::cerr << msg << std::endl;
  exit(1);
}

void Util::Die(const char * msg, const char * more) {
  std::cerr << msg << more << std::endl;
  exit(1);
}

void Util::Die(std::string msg) {
  std::cerr << msg << std::endl;
  exit(1);
}

std::string Util::ShaderArrayName(const char* arrName, int index, const char* memberName) {
  std::stringstream ss;
  ss << arrName << "[" << index <<  "]." << memberName;
  return ss.str();
}
