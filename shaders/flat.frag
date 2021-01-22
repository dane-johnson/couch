#version 330 core

noperspective in vec2 UV;
in vec3 NORMAL;

flat in vec3 AMBIENT;
flat in vec3 DIFFUSE;
flat in vec3 SPECULAR;

out vec4 FragColor;

struct Material {
  vec3 color;
  bool usesColor;
  sampler2D tex;
  bool usesTex;
  float alphaScissor;
  bool unshaded;
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
  if (FragColor.w < material.alphaScissor) {
    discard;
  }

  if (!material.unshaded) {
    FragColor *= vec4(AMBIENT + DIFFUSE + SPECULAR, 1.0);
  }
}
