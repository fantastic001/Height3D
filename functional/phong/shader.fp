#version 120


uniform sampler2D image;

uniform vec4 ambientProduct, diffuseProduct, specularProduct;
uniform vec4 LightPosition;
uniform float shininess;

varying vec3 N;
varying vec3 L;
varying vec3 E;


void main()
{
  vec3 NN = normalize(N);
  vec3 EE = normalize(E);
  vec3 LL = normalize(L);
  vec4 ambient, diffuse, specular;

  vec3 H = normalize(LL+EE);
  float kd = max(dot(LL,NN), 0.0);
  float ks = pow(max(dot(NN, H), 0.0), shininess);

  ambient = ambientProduct;
  diffuse = kd*diffuseProduct;
  specular = ks*specularProduct;
  gl_FragColor = vec4((ambient + diffuse + specular).xyz, 1.0);
}

