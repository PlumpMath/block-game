#ifndef BLOCK_GAME_OPENGL_SHADER_H_
#define BLOCK_GAME_OPENGL_SHADER_H_

namespace block_game
{
  class Shader
  {
  public:
    Shader(const unsigned int, const char*);
    ~Shader();

    void Attach(const unsigned int) const;
    void Detach(const unsigned int) const;

  private:
    const unsigned int id_;
  };
}

#endif
