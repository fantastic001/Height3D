#version 120

vec2 uv;
uniform sampler2D image;

void main()
{
  gl_FragColor = texture2D(image, uv);
}

