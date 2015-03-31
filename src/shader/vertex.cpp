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
  gl_Position.xyz = radius * in_Position;
  gl_Position.w = 1.0;
  gl_Position = rotation * gl_Position;
  gl_Position += position;

  pass_Color.xyz = gl_Normal;
  pass_Color = rotation * pass_Color;
  pass_Color.xy = pass_Color.zz;
  pass_Color *= color;
}

)";
