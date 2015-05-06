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

    IndexBuffer(IndexBuffer&);
    IndexBuffer(IndexBuffer&&);
    IndexBuffer& operator=(IndexBuffer&);
    IndexBuffer& operator=(IndexBuffer&&);

    void Bind();
    static void Unbind();

    void SetData(const GLsizeiptr, const GLvoid*);

    void Draw(const GLsizei, const GLenum) const;

  private:
    static IndexBuffer* bound_;

    GLuint id_;
  };
}

#endif
