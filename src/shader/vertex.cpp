#include "shader/vertex.h"

const char* block_game::vertex_glsl{R"(

#version 120

uniform float radius;
uniform vec3 color;
uniform vec3 position;
uniform mat3 rotation;
uniform mat4 viewProjection;

in vec3 in_Vertex;
in vec3 in_Normal;

varying vec3 pass_Color;

void main()
{
  gl_Position = viewProjection * vec4(position + rotation * (radius * in_Vertex), 1.0);
  pass_Color = color * -(rotation * in_Normal).zzz;
}

)"};
