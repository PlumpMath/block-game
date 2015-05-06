#ifndef BLOCK_GAME_OPENGL_VERTEX_BUFFER_H_
#define BLOCK_GAME_OPENGL_VERTEX_BUFFER_H_

#include <glad/glad.h>

namespace block_game
{
  class VertexBuffer
  {
  public:
    VertexBuffer();
    ~VertexBuffer();

    // The source VertexBuffer points to nothing after copy/move
    VertexBuffer(VertexBuffer&);
    VertexBuffer(VertexBuffer&&);
    VertexBuffer& operator=(VertexBuffer&);
    VertexBuffer& operator=(VertexBuffer&&);

    void Bind();
    static void Unbind();

    void SetData(const GLsizeiptr, const GLvoid*);

  private:
    static VertexBuffer* bound_;

    GLuint id_;
  };
}

#endif
