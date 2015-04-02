#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 110

uniform float radius;
uniform vec3 color;
uniform vec3 position;
uniform mat3 rotation;

attribute vec3 in_Position;

varying vec3 pass_Color;

void main()
{
  gl_Position = vec4(position + rotation * (radius * in_Position), 1.0);
  pass_Color = color * -(rotation * gl_Normal).zzz;
}

)";
