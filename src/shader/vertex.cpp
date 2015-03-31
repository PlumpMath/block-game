#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 110

uniform float radius;
uniform vec3 color;
uniform vec3 position;
uniform mat4 rotation;

attribute vec3 in_Position;

varying vec4 pass_Color;

void main()
{
  gl_Position = position + rotation * vec4(radius * in_Position, 1.0);
  pass_Color = color * vec4((rotation * vec4(gl_Normal, 1.0)).zzz, 1.0);
}

)";
