#include "opengl/program.h"

#include <iostream>
#include <string>
#include <vector>

#include <glad/glad.h>

#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/buffer.h"
#include "opengl/vertex_attribute.h"

namespace
{
  std::string GetSource(const GLuint shader_id)
  {
    GLint source_length;
    glGetShaderiv(shader_id, GL_SHADER_SOURCE_LENGTH, &source_length);

    std::string source(source_length, '\0');
    glGetShaderSource(shader_id, source_length, nullptr, &source[0]);

    return source;
  }

  void Compile(const GLenum shader_type, const GLuint shader_id, const std::string& shader_source)
  {
    const char* source_c_str = shader_source.c_str();
    glShaderSource(shader_id, 1, &source_c_str, nullptr);
    glCompileShader(shader_id);

    GLint is_compiled;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &is_compiled);
    if (!is_compiled)
    {
      GLint info_log_length;
      glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

      std::string info_log(info_log_length, '\0');
      glGetShaderInfoLog(shader_id, info_log_length, nullptr, &info_log[0]);

      std::cerr << "Shader failed to compile as type " << shader_type << "! Source:";
      std::cerr << shader_source;
      std::cerr << "Error log:" << std::endl;
      std::cerr << std::endl;
      std::cerr << info_log << std::endl;
      std::cerr << std::endl;
      std::cerr << "End of error log." << std::endl;
      std::cerr << std::endl;
    }
  }
}

namespace block_game
{
  Program::Program(const std::string& vertex_source, const std::string& fragment_source)
    : id_{glCreateProgram()}, vertex_id_{glCreateShader(GL_VERTEX_SHADER)}, fragment_id_{glCreateShader(GL_FRAGMENT_SHADER)}
  {
    Compile(GL_VERTEX_SHADER, vertex_id_, vertex_source);
    Compile(GL_FRAGMENT_SHADER, fragment_id_, fragment_source);

    glAttachShader(id_, vertex_id_);
    glAttachShader(id_, fragment_id_);

    Link();
  }

  Program::~Program()
  {
    glDeleteProgram(id_);
    glDeleteShader(vertex_id_);
    glDeleteShader(fragment_id_);
  }

  Program::Program(const Program& program) : Program{GetSource(program.vertex_id_), GetSource(program.fragment_id_)}
  {}

  Program& Program::operator=(const Program& program)
  {
    Compile(GL_VERTEX_SHADER, vertex_id_, GetSource(program.vertex_id_));
    Compile(GL_FRAGMENT_SHADER, fragment_id_, GetSource(program.fragment_id_));

    Link();

    return *this;
  }

  Program::Program(Program&& program) : id_{program.id_}, vertex_id_{program.vertex_id_}, fragment_id_{program.fragment_id_}
  {
    program.id_ = 0;
    program.vertex_id_ = 0;
    program.fragment_id_ = 0;
  }

  Program& Program::operator=(Program&& program)
  {
    id_ = program.id_;
    vertex_id_ = program.vertex_id_;
    fragment_id_ = program.fragment_id_;

    program.id_ = 0;
    program.vertex_id_ = 0;
    program.fragment_id_ = 0;

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
    glUniformMatrix2fv(glGetUniformLocation(id_, name.c_str()), 1, true, &matrix[0][0]);
    glUseProgram(0);
  }

  void Program::SetUniformMatrix3(const std::string& name, const Matrix<3>& matrix)
  {
    glUseProgram(id_);
    glUniformMatrix3fv(glGetUniformLocation(id_, name.c_str()), 1, true, &matrix[0][0]);
    glUseProgram(0);
  }

  void Program::SetUniformMatrix4(const std::string& name, const Matrix<4>& matrix)
  {
    glUseProgram(id_);
    glUniformMatrix4fv(glGetUniformLocation(id_, name.c_str()), 1, true, &matrix[0][0]);
    glUseProgram(0);
  }

  void Program::Draw(const Buffer& vertex_buffer, const Buffer& index_buffer,
    const std::vector<VertexAttribute>& attributes) const
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

    glDrawElements(GL_TRIANGLES, index_buffer.GetSize(), GL_UNSIGNED_BYTE, 0);

    for (GLuint i = 0; i < attributes.size(); ++i)
    {
      glDisableVertexAttribArray(i);
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glUseProgram(0);
  }

  void Program::Link() const
  {
    glLinkProgram(id_);

    GLint is_linked = 0;
    glGetProgramiv(id_, GL_LINK_STATUS, &is_linked);
    if (is_linked == GL_FALSE)
    {
      GLint info_log_length = 0;
      glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &info_log_length);

      std::string info_log(info_log_length, '\0');
      glGetProgramInfoLog(id_, info_log_length, &info_log_length, &info_log[0]);

      std::cerr << "Program failed to link! Error log:" << std::endl;
      std::cerr << std::endl;
      std::cerr << info_log << std::endl;
      std::cerr << std::endl;
      std::cerr << "End of error log." << std::endl;
      std::cerr << std::endl;
    }
  }
}
