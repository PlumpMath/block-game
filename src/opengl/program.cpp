#include "opengl/program.h"

#include "glew/glew.h"

#include "general/matrix_4f.h"
#include "opengl/shader.h"

namespace block_game
{
  Program::Program(const Shader& vertex_shader, const Shader& fragment_shader)
    : id_(glCreateProgram()), vertex_shader_(vertex_shader), fragment_shader_(fragment_shader)
  {
    vertex_shader_.Attach(id_);
    fragment_shader_.Attach(id_);

    glLinkProgram(id_);
    glValidateProgram(id_);
  }

  Program::~Program()
  {
    vertex_shader_.Detach(id_);
    fragment_shader_.Detach(id_);

    glDeleteProgram(id_);
  }

  void Program::Use() const
  {
    glUseProgram(id_);
  }

  void Program::SetUniformMatrix4F(const char* name, const Matrix4F& matrix_4f)
  {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, true, *(matrix_4f.elements));
  }
}
