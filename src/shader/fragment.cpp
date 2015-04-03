#include "shader/fragment.h"

const char* block_game::fragment_glsl = R"(

#version 120

varying vec3 pass_Color;

void main()
{
  gl_FragColor = vec4(pass_Color, 1.0);
}

)";
