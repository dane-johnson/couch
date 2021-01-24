#version 330 core

noperspective in vec2 UV;

in vec3 AMBIENT;
in vec3 DIFFUSE;
in vec3 SPECULAR;
flat in float kill;

out vec4 FragColor;

struct Material {
  sampler2D tex;
  bool usesTex;

  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
  int shininess;
  
  float alphaScissor;
  bool unshaded;
  bool cullBack;
};

uniform Material material;

void main() {
  FragColor = vec4(AMBIENT + DIFFUSE + SPECULAR, 1.0);
  
  if (material.usesTex) {
    FragColor *= texture(material.tex, UV);
  }
  
  if (FragColor.w < material.alphaScissor) {
    discard;
  }

  if (material.cullBack && !gl_FrontFacing) {
    discard;
  }

  if (kill == 1.0) {
    discard;
  }
}
