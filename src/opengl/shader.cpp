#include "opengl/shader.h"

#include <iostream>
#include <vector>

namespace block_game
{
  Shader::Shader(const GLenum type, const GLchar* source) : id_{glCreateShader(type)}
  {
    glShaderSource(id_, 1, &source, nullptr);
    glCompileShader(id_);

    int is_compiled;
    glGetShaderiv(id_, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled)
    {
      int max_length;
      glGetShaderiv(id_, GL_INFO_LOG_LENGTH, &max_length);

      std::vector<const char> error_log(max_length);
      glGetShaderInfoLog(id_, max_length, &max_length, &error_log[0]);

      std::cerr << "Shader failed to compile! Source:";
      std::cerr << source;
      std::cerr << "Error log:" << std::endl;
      std::cerr << std::endl;
      for (const char character : error_log)
      {
        std::cerr << character;
      }
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
