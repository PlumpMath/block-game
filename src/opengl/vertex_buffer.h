#ifndef BLOCK_GAME_OPENGL_VERTEX_BUFFER_H_
#define BLOCK_GAME_OPENGL_VERTEX_BUFFER_H_

#include <GL/glew.h>

namespace block_game
{
  class VertexBuffer
  {
  public:
    VertexBuffer();
    ~VertexBuffer();

    void Bind() const;
    static void Unbind();

    void SetData(const GLsizeiptr size, const GLvoid* data, const GLenum usage);

  private:
    GLuint id_;
  };
}

#endif
