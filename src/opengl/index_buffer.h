#ifndef BLOCK_GAME_OPENGL_INDEX_BUFFER_H_
#define BLOCK_GAME_OPENGL_INDEX_BUFFER_H_

#include <glad/glad.h>

namespace block_game
{
  class IndexBuffer
  {
  public:
    IndexBuffer();
    ~IndexBuffer();

    void Bind() const;
    static void Unbind();

    void SetData(const GLsizeiptr size, const GLvoid* data, const GLenum usage);

    void Draw(const GLsizei, const GLenum) const;

  private:
    GLuint id_;
  };
}

#endif
