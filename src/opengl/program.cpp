#include "opengl/program.h"

#include <glad/glad.h>

#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/shader.h"

namespace block_game
{
  Program::Program(const Shader& vertex_shader, const Shader& fragment_shader)
    : id_{glCreateProgram()}, vertex_shader_{vertex_shader}, fragment_shader_{fragment_shader}
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

  Program::Program(Program& program)
    : id_{program.id_}, vertex_shader_{program.vertex_shader_}, fragment_shader_{program.fragment_shader_}
  {
    program.id_ = 0;
  }

  Program::Program(Program&& program)
    : id_{program.id_}, vertex_shader_{program.vertex_shader_}, fragment_shader_{program.fragment_shader_}
  {
    program.id_ = 0;
  }

  Program& Program::operator=(Program& program)
  {
    id_ = program.id_;
    program.id_ = 0;
    return *this;
  }

  Program& Program::operator=(Program&& program)
  {
    id_ = program.id_;
    program.id_ = 0;
    return *this;
  }

  void Program::Bind() const
  {
    glUseProgram(id_);
  }

  void Program::Unbind()
  {
    glUseProgram(0);
  }

  GLint Program::GetAttribLocation(const GLchar* name)
  {
    assert(name);
    return glGetAttribLocation(id_, name);
  }

  void Program::SetUniformFloat(const GLchar* name, const GLfloat value)
  {
    assert(name);
    glUniform1f(glGetUniformLocation(id_, name), value);
  }

  void Program::SetUniformVector2(const GLchar* name, const Vector<2>& vector_2)
  {
    assert(name);
    glUniform2f(glGetUniformLocation(id_, name), vector_2[0], vector_2[1]);
  }

  void Program::SetUniformVector3(const GLchar* name, const Vector<3>& vector_3)
  {
    assert(name);
    glUniform3f(glGetUniformLocation(id_, name), vector_3[0], vector_3[1], vector_3[2]);
  }

  void Program::SetUniformMatrix2(const GLchar* name, const Matrix<2>& matrix)
  {
    assert(name);
    glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }

  void Program::SetUniformMatrix3(const GLchar* name, const Matrix<3>& matrix)
  {
    assert(name);
    glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }

  void Program::SetUniformMatrix4(const GLchar* name, const Matrix<4>& matrix)
  {
    assert(name);
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }
}
