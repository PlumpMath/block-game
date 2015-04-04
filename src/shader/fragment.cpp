#include "shader/fragment.h"

const char* block_game::fragment_glsl = R"(

#version 120

in vec3 pass_Color;

out vec4 out_Color;

void main()
{
  out_Color = vec4(pass_Color, 1.0);
}

)";
