#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

namespace block_game
{
  template<int order>
  struct Matrix;

  struct Vector2F;
  struct Vector3F;
  class Shader;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    void Use() const;

    void SetUniformFloat(const char*, const float);
    void SetUniformVector2F(const char*, const Vector2F&);
    void SetUniformVector3F(const char*, const Vector3F&);
    void SetUniformMatrix2(const char*, const Matrix<2>&);
    void SetUniformMatrix3(const char*, const Matrix<3>&);
    void SetUniformMatrix4(const char*, const Matrix<4>&);

  private:
    const int id_;

    const Shader& vertex_shader_;
    const Shader& fragment_shader_;
  };
}

#endif
