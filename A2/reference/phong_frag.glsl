precision mediump float; // It is required to set a floating point precision in all fragment shaders.

// Interpolated values from vertex shader
varying vec3 normalInterp; // Normal
varying vec3 vertPos; // Vertex position
varying vec3 viewVec; // Interpolated view vector

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
  // Your solution should go here.
  // Only the ambient colour calculations have been provided as an example.
  
  vec3 ambient, diffuse, specular; 
  vec3 normal = normalize(normalInterp);
  vec3 lightDir = normalize(vec3(lightPos - vertPos));
  vec3 viewDir = normalize(viewVec);
  vec3 reflectDir = reflect(-lightDir, normal);

  ambient = ambientColor * Ka;

  diffuse = diffuseColor * Kd * max(dot(lightdir,norm), 0.0);

  specular = specularColor * Ks * pow(max(dot(reflec, view), 0.0), shininessVal);
  
  gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}