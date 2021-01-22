#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 uv;

uniform mat4 MODEL;
uniform mat4 VIEW;
uniform mat4 PROJECTION;

out vec3 UV;
out vec3 NORMAL;
flat out vec3 LIGHT;

struct DirectionalLight {
  vec3 direction;
  vec3 color;
  float ambient;
  float diffuse;
  float specular;
};

uniform DirectionalLight directionalLight;

void main() {
  vec4 vertex = PROJECTION * VIEW * MODEL * vec4(pos, 1.0);
  gl_Position = vertex;
  UV = vec3(uv * vertex.z, vertex.z);

  NORMAL = (VIEW * MODEL * vec4(normal, 0.0)).xyz;

  // Flat shading, we compute light per vertex
  vec3 ambient = directionalLight.ambient * directionalLight.color;

  vec3 direction = -(VIEW * vec4(directionalLight.direction, 0.0)).xyz;
  float diff = dot(normalize(direction), normalize(NORMAL));
  diff = max(diff, 0.0);
  vec3 diffuse = directionalLight.diffuse * diff * directionalLight.color;

  vec3 viewDir = (VIEW * MODEL * vec4(pos, 1.0)).xyz;
  vec3 reflectionDir = reflect(normalize(direction), normalize(NORMAL));
  float spec = dot(viewDir, reflectionDir);
  spec = max(spec, 0.0);
  spec = pow(spec, 2);
  vec3 specular = directionalLight.specular * spec * directionalLight.color;

  LIGHT = ambient + diffuse + specular;
}
