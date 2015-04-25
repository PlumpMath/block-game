#include "opengl/index_buffer.h"

#include <glad/glad.h>

namespace block_game
{
  IndexBuffer::IndexBuffer()
  {
    glGenBuffers(1, &id_);
  }

  IndexBuffer::~IndexBuffer()
  {
    glDeleteBuffers(1, &id_);
  }

  void IndexBuffer::Bind() const
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
  }

  void IndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  }

  void IndexBuffer::SetData(const GLsizeiptr size, const GLvoid* data, const GLenum usage)
  {
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
  }

  void IndexBuffer::Draw(const GLsizei count, const GLenum type) const
  {
    glDrawElements(GL_TRIANGLES, count, type, (void*) 0);
  }
}
