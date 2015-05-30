#version 120

uniform vec3 position;
uniform mat3 rotation;
uniform mat4 viewProjection;

attribute vec3 in_Vertex;
attribute vec3 in_Normal;
attribute vec3 in_Color;

varying vec3 pass_Color;

void main()
{
  gl_Position = viewProjection * vec4(position + rotation * in_Vertex, 1.0);
  pass_Color = in_Color * -(rotation * in_Normal).z;
}
