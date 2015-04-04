#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 120

uniform float radius;
uniform vec3 color;
uniform vec3 position;
uniform mat3 rotation;

in vec3 in_Vertex;
in vec3 in_Normal;

out vec3 pass_Color;

void main()
{
  gl_Position = vec4(position + rotation * (radius * in_Vertex), 1.0);
  pass_Color = color * -(rotation * in_Normal).zzz;
}

)";
