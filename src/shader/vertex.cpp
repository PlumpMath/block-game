#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 120

uniform float radius;
uniform vec3 color;
uniform vec3 position;
uniform mat3 rotation;

varying vec3 pass_Color;

void main()
{
  gl_Position = vec4(position + rotation * (radius * gl_Vertex.xyz), 1.0);
  pass_Color = color * -(rotation * gl_Normal).zzz;
}

)";
