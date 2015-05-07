#include "shader/fragment.h"

#include <string>

const std::string block_game::fragment_glsl{R"(

#version 120

varying vec3 pass_Color;

void main()
{
  gl_FragColor = vec4(pass_Color, 1.0);
}

)"};
