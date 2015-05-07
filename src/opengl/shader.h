#ifndef BLOCK_GAME_OPENGL_SHADER_H_
#define BLOCK_GAME_OPENGL_SHADER_H_

#include <string>

#include <glad/glad.h>

namespace block_game
{
  class Shader
  {
  public:
    Shader(const GLenum, const std::string&);
    ~Shader();

    Shader(const Shader&);
    Shader& operator=(const Shader&);

    Shader(Shader&&);
    Shader& operator=(Shader&&);

    void Attach(const GLuint) const;
    void Detach(const GLuint) const;

  private:
    void Compile(const std::string&) const;

    GLuint id_;
  };
}

#endif
