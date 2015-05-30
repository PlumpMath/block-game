#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

#include <string>
#include <vector>

#include <glad/glad.h>

#include "opengl/vertex_attribute.h"

namespace block_game {
class Buffer;
template<int> class Matrix;
template<int> class Vector;

class Program {
public:
  Program(const std::string& vertex_source, const std::string& fragment_source);
  ~Program();
  Program(const Program& program);
  Program(Program&& program);
  Program& operator=(Program program);

  void SetUniformFloat(const std::string& name, const GLfloat value);
  void SetUniformVector2(const std::string& name, const Vector<2>& value);
  void SetUniformVector3(const std::string& name, const Vector<3>& value);
  void SetUniformMatrix2(const std::string& name, const Matrix<2>& value);
  void SetUniformMatrix3(const std::string& name, const Matrix<3>& value);
  void SetUniformMatrix4(const std::string& name, const Matrix<4>& value);

  void Draw(const Buffer& vertex_buffer, const Buffer& index_buffer, const std::vector<VertexAttribute>& attributes) const;

private:
  GLuint id_;
  GLuint vertex_id_;
  GLuint fragment_id_;
};
}

#endif
