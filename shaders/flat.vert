#version 330 core

layout (location = 0) in vec3 pos;

// uniform mat4 MODEL;
// uniform mat4 VIEW;
// uniform mat4 PROJECTION;

void main() {
  //gl_Position = MODEL * VIEW * PROJECTION * vec4(pos, 1.0);
  gl_Position = vec4(pos, 1.0);
}
