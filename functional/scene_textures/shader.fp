#version 120

varying vec2 st;
uniform sampler2D image;
varying vec4 color;

void main()
{
  gl_FragColor = texture2D(image, st);
}

