#ifndef BLOCK_GAME_OPENGL_SHADER_H_
#define BLOCK_GAME_OPENGL_SHADER_H_

namespace block_game
{
  class Shader
  {
  public:
    Shader(const int, const char*);
    ~Shader();

    void Attach(const int) const;
    void Detach(const int) const;

  private:
    const int id_;
  };
}

#endif
