#include "opengl/shader.h"

#include <iostream>
#include <string>

namespace block_game
{
  Shader::Shader(const GLenum type, const GLchar* source) : id_{glCreateShader(type)}
  {
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);

    GLint is_compiled;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled)
    {
      GLint max_length;
      glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &max_length);

      std::string error_log(max_length, '\0');
      glGetShaderInfoLog(id_, max_length, &max_length, &error_log[0]);

      std::cerr << "Shader failed to compile as type " << type << "! Source:";
      std::cerr << source;
      std::cerr << "Error log:" << std::endl;
      std::cerr << std::endl;
      std::cerr << error_log;
      std::cerr << std::endl;
      std::cerr << std::endl;
      std::cerr << "End of error log." << std::endl;
      std::cerr << std::endl;
    }
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
