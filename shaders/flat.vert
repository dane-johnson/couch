#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

void main() {
  gl_Position = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
}
