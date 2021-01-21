#version 330 core

in vec3 UV;
in vec3 NORMAL;

out vec4 FragColor;

struct Material {
  vec3 color;
  bool usesColor;
  sampler2D tex;
  bool usesTex;
  float alphaScissor;
  bool unshaded;
};

struct DirectionalLight {
  vec3 direction;
  vec3 color;
  float ambient;
  float diffuse;
  float specular;
};

uniform Material material;
uniform DirectionalLight directionalLight;

void main() {
  FragColor = vec4(0.0);
  if (material.usesColor) {
    FragColor += vec4(material.color, 1.0);
  }
  if (material.usesTex) {
    FragColor += texture(material.tex, UV.xy / UV.z);
  }
  if (FragColor.w < material.alphaScissor) {
    discard;
  }

  if (!material.unshaded) {
    vec3 ambient = directionalLight.ambient * directionalLight.color;
    ambient = max(ambient, 0.0);
    
    vec3 diffuse = directionalLight.diffuse * dot(directionalLight.direction, NORMAL) * directionalLight.color;
    diffuse = max(diffuse, 0.0);
    
    FragColor *= vec4(ambient + diffuse, 1.0);
  }
}
