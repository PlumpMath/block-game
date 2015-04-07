#ifndef BLOCK_GAME_OPENGL_SHADER_H_
#define BLOCK_GAME_OPENGL_SHADER_H_

#include <GL/glew.h>

namespace block_game
{
  class Shader
  {
  public:
    Shader(const GLenum, const GLchar*);
    ~Shader();

    void Attach(const GLuint) const;
    void Detach(const GLuint) const;

  private:
    const GLuint id_;
  };
}

#endif
