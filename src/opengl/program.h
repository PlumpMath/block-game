#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

#include "glew/glew.h"

namespace block_game
{
  template<int> struct Matrix;
  struct Vector2F;
  struct Vector3F;
  class Shader;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    void Use() const;

    void SetUniformFloat(const GLchar*, const GLfloat);
    void SetUniformVector2F(const GLchar*, const Vector2F&);
    void SetUniformVector3F(const GLchar*, const Vector3F&);
    void SetUniformMatrix2(const GLchar*, const Matrix<2>&);
    void SetUniformMatrix3(const GLchar*, const Matrix<3>&);
    void SetUniformMatrix4(const GLchar*, const Matrix<4>&);

  private:
    const GLuint id_;

    const Shader& vertex_shader_;
    const Shader& fragment_shader_;
  };
}

#endif
