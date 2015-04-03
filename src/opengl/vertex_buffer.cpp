#include "opengl/vertex_buffer.h"

namespace block_game
{
  VertexBuffer::VertexBuffer()
  {
    glGenBuffers(1, &id_);
  }

  VertexBuffer::~VertexBuffer()
  {
    glDeleteBuffers(1, &id_);
  }

  void VertexBuffer::Bind() const
  {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
  }

  void VertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
  }

  void VertexBuffer::SetData(const GLsizeiptr size, const GLvoid* data, const GLenum usage)
  {
    glBufferData(GL_ARRAY_BUFFER, size, data, usage);
  }
}
