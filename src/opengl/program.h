#ifndef BLOCK_GAME_OPENGL_PROGRAM_H_
#define BLOCK_GAME_OPENGL_PROGRAM_H_

namespace block_game
{
  struct Matrix4F;
  class Shader;

  class Program
  {
  public:
    Program(const Shader&, const Shader&);
    ~Program();

    void Use() const;
    void SetUniformMatrix4F(const char*, const Matrix4F&);

  private:
    const int id_;

    const Shader& vertex_shader_;
    const Shader& fragment_shader_;
  };
}

#endif
