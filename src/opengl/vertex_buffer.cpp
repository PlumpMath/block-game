#include "opengl/vertex_buffer.h"

#include <cassert>

#include <glad/glad.h>

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

  VertexBuffer::VertexBuffer(VertexBuffer& vertex_buffer) : id_{vertex_buffer.id_}
  {
    vertex_buffer.id_ = 0;
  }

  VertexBuffer::VertexBuffer(VertexBuffer&& vertex_buffer) : id_{vertex_buffer.id_}
  {
    vertex_buffer.id_ = 0;
  }

  VertexBuffer& VertexBuffer::operator=(VertexBuffer& vertex_buffer)
  {
    id_ = vertex_buffer.id_;
    vertex_buffer.id_ = 0;
    return *this;
  }

  VertexBuffer& VertexBuffer::operator=(VertexBuffer&& vertex_buffer)
  {
    id_ = vertex_buffer.id_;
    vertex_buffer.id_ = 0;
    return *this;
  }

  void VertexBuffer::Bind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, id_);
    bound_ = this;
  }

  void VertexBuffer::Unbind()
  {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    bound_ = nullptr;
  }

  void VertexBuffer::SetData(const GLsizeiptr size, const GLvoid* data)
  {
    assert(bound_ == this && size >= 0 && data);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  VertexBuffer* VertexBuffer::bound_{nullptr};
}
