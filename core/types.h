#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

typedef glm::vec3 Vector3;
typedef glm::mat4 Matrix;
typedef std::string Name;
typedef GLuint Id;

Vector3 operator*(const Vector3 &r, const float &l);
Vector3 operator+(const Vector3 &r, const Vector3 &l);

#endif /* TYPES_H */
