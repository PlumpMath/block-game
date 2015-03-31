#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

namespace block_game
{
  struct Matrix3F;
  struct Matrix4F;
  struct Vector3F;
  class Shader;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    void Use() const;

    void SetUniformFloat(const char*, const float);
    void SetUniformVector3F(const char*, const Vector3F&);
    void SetUniformMatrix3F(const char*, const Matrix3F&);
    void SetUniformMatrix4F(const char*, const Matrix4F&);

  private:
    const int id_;

    const Shader& vertex_shader_;
    const Shader& fragment_shader_;
  };
}

#endif
