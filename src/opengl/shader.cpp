#include "opengl/shader.h"

#include "glew/glew.h"

namespace block_game
{
  Shader::Shader(const int type, const char* source) : id_(glCreateShader(type))
  {
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);
  }

  Shader::~Shader()
  {
    glDeleteShader(id_);
  }

  void Shader::Attach(const int program_id) const
  {
    glAttachShader(program_id, id_);
  }

  void Shader::Detach(const int program_id) const
  {
    glDetachShader(program_id, id_);
  }
}
