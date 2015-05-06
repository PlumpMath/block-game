#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

#include <glad/glad.h>

namespace block_game
{
  template<int>
  struct Matrix;
  class Shader;
  template<int>
  struct Vector;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    // The source Program points to nothing after copy/move
    Program(Program&);
    Program(Program&&);
    Program& operator=(Program&);
    Program& operator=(Program&&);

    void Bind();
    static void Unbind();

    GLint GetAttribLocation(const GLchar*);

    void SetUniformFloat(const GLchar*, const GLfloat);
    void SetUniformVector2(const GLchar*, const Vector<2>&);
    void SetUniformVector3(const GLchar*, const Vector<3>&);
    void SetUniformMatrix2(const GLchar*, const Matrix<2>&);
    void SetUniformMatrix3(const GLchar*, const Matrix<3>&);
    void SetUniformMatrix4(const GLchar*, const Matrix<4>&);

  private:
    static Program* bound_;

    GLuint id_;

    const Shader& vertex_shader_;
    const Shader& fragment_shader_;
  };
}

#endif
