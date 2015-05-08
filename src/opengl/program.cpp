#include "opengl/program.h"

#include <string>
#include <vector>

#include <glad/glad.h>

#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/buffer.h"
#include "opengl/shader.h"
#include "opengl/vertex_attribute.h"

namespace block_game
{
  Program::Program(const Shader& vertex_shader, const Shader& fragment_shader)
    : id_{glCreateProgram()}, vertex_shader_{&vertex_shader}, fragment_shader_{&fragment_shader}
  {
    vertex_shader_->Attach(id_);
    fragment_shader_->Attach(id_);

    glLinkProgram(id_);
    glValidateProgram(id_);
  }

  Program::~Program()
  {
    vertex_shader_->Detach(id_);
    fragment_shader_->Detach(id_);

    glDeleteProgram(id_);
  }

  Program::Program(const Program& program)
  {}

  Program& Program::operator=(const Program& program)
  {
    return *this;
  }

  Program::Program(Program&& program)
    : id_{program.id_}, vertex_shader_{program.vertex_shader_}, fragment_shader_{program.fragment_shader_}
  {
    program.id_ = 0;
  }

  Program& Program::operator=(Program&& program)
  {
    id_ = program.id_;
    vertex_shader_ = program.vertex_shader_;
    fragment_shader_ = program.fragment_shader_;
    program.id_ = 0;
    return *this;
  }

  void Program::SetUniformFloat(const std::string& name, const GLfloat value)
  {
    glUseProgram(id_);
    glUniform1f(glGetUniformLocation(id_, name.c_str()), value);
    glUseProgram(0);
  }

  void Program::SetUniformVector2(const std::string& name, const Vector<2>& vector_2)
  {
    glUseProgram(id_);
    glUniform2f(glGetUniformLocation(id_, name.c_str()), vector_2[0], vector_2[1]);
    glUseProgram(0);
  }

  void Program::SetUniformVector3(const std::string& name, const Vector<3>& vector_3)
  {
    glUseProgram(id_);
    glUniform3f(glGetUniformLocation(id_, name.c_str()), vector_3[0], vector_3[1], vector_3[2]);
    glUseProgram(0);
  }

  void Program::SetUniformMatrix2(const std::string& name, const Matrix<2>& matrix)
  {
    glUseProgram(id_);
    glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, true, *(matrix.elements));
    glUseProgram(0);
  }

  void Program::SetUniformMatrix3(const std::string& name, const Matrix<3>& matrix)
  {
    glUseProgram(id_);
    glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, true, *(matrix.elements));
    glUseProgram(0);
  }

  void Program::SetUniformMatrix4(const std::string& name, const Matrix<4>& matrix)
  {
    glUseProgram(id_);
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, true, *(matrix.elements));
    glUseProgram(0);
  }

  void Program::Draw(const Buffer& vertex_buffer, const Buffer& index_buffer,
    const std::vector<const VertexAttribute>& attributes)
  {
    assert(vertex_buffer.target_ == GL_ARRAY_BUFFER);
    assert(index_buffer.target_ == GL_ELEMENT_ARRAY_BUFFER);

    glUseProgram(id_);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer.id_);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer.id_);

    for (GLuint i = 0; i < attributes.size(); ++i)
    {
      glEnableVertexAttribArray(i);
    }

    for (const VertexAttribute& attribute : attributes)
    {
      glVertexAttribPointer(glGetAttribLocation(id_, attribute.name.c_str()), attribute.size, attribute.type,
        attribute.normalized, attribute.stride, reinterpret_cast<GLvoid*>(attribute.pointer));
    }

    glDrawElements(GL_TRIANGLES, index_buffer.size_, GL_UNSIGNED_BYTE, 0);

    for (GLuint i = 0; i < attributes.size(); ++i)
    {
      glDisableVertexAttribArray(i);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
  }
}
