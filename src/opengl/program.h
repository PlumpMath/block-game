#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

#include <string>
#include <vector>

#include <glad/glad.h>

#include "opengl/vertex_attribute.h"

namespace block_game
{
  class Buffer;
  template<int>
  class Matrix;
  template<int>
  class Vector;

  class Program
  {
  public:
    Program(const std::string&, const std::string&);
    ~Program();
    Program(const Program&);
    Program(Program&&);
    Program& operator=(Program);

    void SetUniformFloat(const std::string&, const GLfloat);
    void SetUniformVector2(const std::string&, const Vector<2>&);
    void SetUniformVector3(const std::string&, const Vector<3>&);
    void SetUniformMatrix2(const std::string&, const Matrix<2>&);
    void SetUniformMatrix3(const std::string&, const Matrix<3>&);
    void SetUniformMatrix4(const std::string&, const Matrix<4>&);

    void Draw(const Buffer&, const Buffer&, const std::vector<VertexAttribute>&) const;

  private:
    GLuint id_;
    GLuint vertex_id_;
    GLuint fragment_id_;
  };
}

#endif
