#include "opengl/program.h"

#include "glew/glew.h"

#include "general/matrix_3f.h"
#include "general/matrix_4f.h"
#include "general/vector_3f.h"
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

  void Program::SetUniformFloat(const char* name, const float value)
  {
    glUniform1f(glGetUniformLocation(id_, name), value);
  }

  void Program::SetUniformVector3F(const char* name, const Vector3F& vector_3f)
  {
    glUniform3f(glGetUniformLocation(id_, name), vector_3f.x, vector_3f.y, vector_3f.z);
  }

  void Program::SetUniformMatrix3F(const char* name, const Matrix3F& matrix_3f)
  {
    glUniformMatrix3fv(glGetUniformLocation(id_, name), 1, true, *(matrix_3f.elements));
  }

  void Program::SetUniformMatrix4F(const char* name, const Matrix4F& matrix_4f)
  {
    glUniformMatrix4fv(glGetUniformLocation(id_, name), 1, true, *(matrix_4f.elements));
  }
}
