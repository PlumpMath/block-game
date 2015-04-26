#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

#include <glad/glad.h>

namespace block_game
{
  template<int>
  struct Matrix;
  class Shader;
  struct Vector2F;
  struct Vector3F;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    void Bind() const;
    static void Unbind();

    GLint GetAttribLocation(const GLchar*);

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
