#include "opengl/program.h"

#include <glad/glad.h>

#include "general/matrix.h"
#include "general/vector_2f.h"
#include "general/vector_3f.h"
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
    return glGetAttribLocation(id_, name);
  }

  void Program::SetUniformFloat(const GLchar* name, const GLfloat value)
  {
    glUniform1f(glGetUniformLocation(id_, name), value);
  }

  void Program::SetUniformVector2F(const GLchar* name, const Vector2F& vector_2f)
  {
    glUniform2f(glGetUniformLocation(id_, name), vector_2f.x, vector_2f.y);
  }

  void Program::SetUniformVector3F(const GLchar* name, const Vector3F& vector_3f)
  {
    glUniform3f(glGetUniformLocation(id_, name), vector_3f.x, vector_3f.y, vector_3f.z);
  }

  void Program::SetUniformMatrix2(const GLchar* name, const Matrix<2>& matrix)
  {
    glUniformMatrix2fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }

  void Program::SetUniformMatrix3(const GLchar* name, const Matrix<3>& matrix)
  {
    glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }

  void Program::SetUniformMatrix4(const GLchar* name, const Matrix<4>& matrix)
  {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, true, *(matrix.elements));
  }
}
