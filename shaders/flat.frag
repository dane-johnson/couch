#version 330 core

in vec3 UV;

struct Material {
  vec3 color;
  bool usesColor;
  sampler2D tex;
  bool usesTex;
};

uniform Material material;

void main() {
  gl_FragColor = vec4(0.0);
  if (material.usesColor) {
    gl_FragColor += vec4(material.color, 1.0);
  }
  if (material.usesTex) {
    gl_FragColor += texture(material.tex, UV.xy / UV.z);
  }
  if (gl_FragColor.w < 0.99) {
    discard;
  }
}
