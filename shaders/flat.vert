#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;
uniform mat3 NORMAL;

noperspective out vec2 UV; // PSX use affine texture mapping

out vec3 AMBIENT;
out vec3 DIFFUSE;
out vec3 SPECULAR;

flat out float kill;

const float cullDistance = 100.0;

struct DirectionalLight {
  vec3 direction;
  vec3 color;
  float ambient;
  float diffuse;
  float specular;
};

struct PointLight {
  vec3 pos;
  float radius;
  vec3 color;
  float ambient;
  float diffuse;
  float specular;
};
#define NUM_POINT_LIGHTS 4
uniform PointLight pointLights[NUM_POINT_LIGHTS];

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

float calcDiffuseIntensity(in vec3 direction, in vec3 normal) {
  float diff = dot(normalize(direction), normalize(normal));
  return max(diff, 0.0);
}

float calcSpecularIntensity(in vec3 direction, in vec3 normal, in int shininess) {
  vec3 viewDir = normalize((VIEW * MODEL * vec4(pos, 1.0)).xyz);
  vec3 reflectionDir = reflect(normalize(direction), normalize(normal));
  float spec = dot(viewDir, reflectionDir);
  spec = max(spec, 0.0);
  spec = pow(spec, shininess);
  return spec;
}

void calcDirectionalLight(in vec3 normal) {
  AMBIENT += directionalLight.ambient * directionalLight.color * material.ambient;

  vec3 direction = -(VIEW * vec4(directionalLight.direction, 0.0)).xyz;
  DIFFUSE += directionalLight.diffuse * directionalLight.color * material.diffuse * calcDiffuseIntensity(direction, normal);

  SPECULAR += directionalLight.color * material.specular * calcSpecularIntensity(direction, normal, material.shininess);
}

void calcPointLight(in vec3 normal, in PointLight pointLight) {
  vec3 direction = vec3(VIEW * vec4(pointLight.pos, 1.0) - VIEW * MODEL * vec4(pos, 1.0)).xyz;
  float dist = length(direction);
  
  float attenuation = max(1.0 - dist * dist / pointLight.radius / pointLight.radius, 0.0);
  AMBIENT += pointLight.color * material.ambient * pointLight.ambient * attenuation;

  DIFFUSE += pointLight.color * pointLight.diffuse * material.diffuse * calcDiffuseIntensity(direction, normal);

  SPECULAR += pointLight.color * material.specular * calcSpecularIntensity(direction, normal, material.shininess);
}

void main() {
  vec4 vertex = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
  gl_Position = vertex;
  if (length(vertex) > cullDistance) {
    kill = 1.0;
  } else {
    kill = 0.0;
  }

  UV = uv;

  vec3 my_normal = (VIEW * mat4(NORMAL) * vec4(normal, 0.0)).xyz;

  // Flat shading, we compute light per vertex
  AMBIENT = vec3(0.0);
  DIFFUSE = vec3(0.0);
  SPECULAR = vec3(0.0);

  calcDirectionalLight(my_normal);

  // PointLights
  for(int i = 0; i < NUM_POINT_LIGHTS; i++) {
    calcPointLight(my_normal, pointLights[i]);
  }
}
