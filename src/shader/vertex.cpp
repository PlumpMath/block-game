#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 110

uniform mat4 matrix;

attribute vec4 in_Position;

varying vec4 pass_Color;

void main(void)
{
  gl_Position = matrix * in_Position;

  pass_Color = gl_Color * vec4(gl_Normal.z, gl_Normal.z, gl_Normal.z, 1.0);
}

)";
