#include "shader/fragment.h"

const char* block_game::fragment_glsl = R"(

#version 110

varying vec4 pass_Color;

void main()
{
  gl_FragColor = pass_Color;
}

)";
