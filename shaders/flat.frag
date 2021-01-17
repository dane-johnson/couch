#version 330 core

in vec2 UV;

out vec4 FragColor;

struct Material {
  vec3 color;
  bool usesColor;
  sampler2D tex;
  bool usesTex;
};

uniform Material material;

void main() {
  FragColor = vec4(0.0);
  if (material.usesColor) {
    FragColor += vec4(material.color, 1.0);
  }
  if (material.usesTex) {
    FragColor += texture(material.tex, UV);
  }
}
