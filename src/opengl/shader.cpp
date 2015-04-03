#include "opengl/shader.h"

namespace block_game
{
  Shader::Shader(const GLenum type, const GLchar* source) : id_(glCreateShader(type))
  {
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);
  }

  Shader::~Shader()
  {
    glDeleteShader(id_);
  }

  void Shader::Attach(const GLuint program_id) const
  {
    glAttachShader(program_id, id_);
  }

  void Shader::Detach(const GLuint program_id) const
  {
    glDetachShader(program_id, id_);
  }
}
