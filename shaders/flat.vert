#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

out vec2 UV;

void main() {
  gl_Position = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
  UV = uv;
}
