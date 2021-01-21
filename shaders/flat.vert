#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

out vec3 UV;
out vec3 NORMAL;

void main() {
  vec4 vertex = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
  gl_Position = vertex;
  UV = vec3(uv * vertex.z, vertex.z);
  NORMAL = normal;
}
