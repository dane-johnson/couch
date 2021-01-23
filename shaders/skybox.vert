#version 330 core

layout (location = 0) in vec3 pos;

out vec3 UV;

uniform mat4 VIEW; // Assuming this is free of translation
uniform mat4 PROJECTION;

void main() {
  UV = pos;
  vec4 projectedPos = PROJECTION * VIEW * vec4(pos, 1.0);
  gl_Position = projectedPos.xyww;
}
