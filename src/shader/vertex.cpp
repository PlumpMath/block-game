#include "shader/vertex.h"

const char* block_game::vertex_glsl = R"(

#version 110

uniform mat4 position_Matrix;
uniform mat4 normal_Matrix;

attribute vec4 in_Position;

varying vec4 pass_Color;

void main(void)
{
  gl_Position = position_Matrix * in_Position;

  vec4 transformed_Normal = normal_Matrix * vec4(gl_Normal.x, gl_Normal.y, gl_Normal.z, 1.0);

  pass_Color = gl_Color * vec4(transformed_Normal.z, transformed_Normal.z, transformed_Normal.z, 1.0);
}

)";
