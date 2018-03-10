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

// HINT: Use the built-in variable gl_FragCoord to get the screen-space coordinates

void main() {
  // Your solution should go here.
  // Only the background color calculations have been provided as an example.

  vec3 ambient, diffuse; 
  vec3 normal = normalize(normalInterp);
  vec3 viewDir = normalize(viewVec);
  vec3 lightDir = normalize(lightPos - vertPos);

  ambient = ambientColor * Ka;

  diffuse = diffuseColor * Kd * max(dot(lightDir,norm), 0.0);

  vec2 pixel = floor(vec2(gl_FragCoord.xy));
  float thick = 10.0;
  pixel = mod(pixel, vec2(thickness));
  float b = thick / 2.0;
  float a = distance(pixel, vec2(b)) / (thick * 0.65);
  if (a >= 0.03)
	  a += diffuse.r + diffuse.g + diffuse.b;
  float circles = clamp(pow(a, 5.0), 0.0, 1.0);

  gl_FragColor = vec4((ambientColor * (1.0 - circles)) + (diffuseColor * circles), 1.0);
}