precision mediump float; // It is required to set a floating point precision in all fragment shaders.

// Interpolated values from vertex shader
varying vec3 normalInterp; // Normal
varying vec3 vertPos; // Vertex position
varying vec3 viewVec; // Interpolated viewDirvector

// uniform values remain the same across the scene
uniform float Ka;   // Ambient reflection coefficient
uniform float Kd;   // Diffuse reflection coefficient
uniform float Ks;   // Specular reflection coefficient
uniform float shininessVal; // Shininess

// Material color
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;

uniform vec3 lightPos; // Light position in camera space

void main() {
  // Your solution should go here
  // Only the ambient colour calculations have been provided as an example.
  // Cel shading is basically like Phong but with "stages" that are rounded to.
  
  vec3 ambient, diffuse, specular; 
  vec3 normal = normalize(normalInterp);
  vec3 lightDir = normalize(lightPos - vertPos);
  vec3 viewDir = normalize(-vertPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  ambient = ambientColor * Ka;

  if (max(dot(lightDir,norm), 0.0) > 0.7)
  	diffuse = diffuseColor * Kd * 1.0;
  else if (max(dot(lightDir,norm), 0.0) > 0.5)
  	diffuse = diffuseColor * Kd * 0.7;
  else if (max(dot(lightDir,norm), 0.0) > 0.3)
  	diffuse = diffuseColor * Kd * 0.4;
  else 
  	diffuse = 0.0;

  specular = 0.0;
  if (max(dot(reflectDir,viewDir),0.0) > 0.9)
  	specular = specularColor * Ks;

  gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}