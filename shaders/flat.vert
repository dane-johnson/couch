#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

noperspective out vec2 UV; // PSX use affine texture mapping
out vec3 NORMAL;

out vec3 AMBIENT;
out vec3 DIFFUSE;
out vec3 SPECULAR;

struct DirectionalLight {
  vec3 direction;
  vec3 color;
  float ambient;
  float diffuse;
  float specular;
};

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

uniform DirectionalLight directionalLight;
uniform Material material;

void main() {
  vec4 vertex = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
  gl_Position = vertex;

  UV = uv;

  NORMAL = (VIEW * MODEL * vec4(normal, 0.0)).xyz;

  // Flat shading, we compute light per vertex
  AMBIENT = directionalLight.ambient * directionalLight.color * material.ambient;

  vec3 direction = -(VIEW * vec4(directionalLight.direction, 0.0)).xyz;
  float diff = dot(normalize(direction), normalize(NORMAL));
  diff = max(diff, 0.0);
  DIFFUSE = directionalLight.diffuse * diff * directionalLight.color * material.diffuse;

  vec3 viewDir = normalize((VIEW * MODEL * vec4(pos, 1.0)).xyz);
  vec3 reflectionDir = reflect(normalize(direction), normalize(NORMAL));
  float spec = dot(viewDir, reflectionDir);
  spec = max(spec, 0.0);
  spec = pow(spec, material.shininess);
  SPECULAR = directionalLight.color * (spec * material.specular);
}
