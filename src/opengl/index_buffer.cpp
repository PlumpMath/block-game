#include "opengl/index_buffer.h"

#include <cassert>

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

  IndexBuffer::IndexBuffer(IndexBuffer& index_buffer) : id_{index_buffer.id_}
  {
    index_buffer.id_ = 0;
  }

  IndexBuffer::IndexBuffer(IndexBuffer&& index_buffer) : id_{index_buffer.id_}
  {
    index_buffer.id_ = 0;
  }

  IndexBuffer& IndexBuffer::operator=(IndexBuffer& index_buffer)
  {
    id_ = index_buffer.id_;
    index_buffer.id_ = 0;
    return *this;
  }

  IndexBuffer& IndexBuffer::operator=(IndexBuffer&& index_buffer)
  {
    id_ = index_buffer.id_;
    index_buffer.id_ = 0;
    return *this;
  }

  void IndexBuffer::Bind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
    bound_ = this;
  }

  void IndexBuffer::Unbind()
  {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    bound_ = nullptr;
  }

  void IndexBuffer::SetData(const GLsizeiptr size, const GLvoid* data)
  {
    assert(bound_ == this && size >= 0 && data);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
  }

  void IndexBuffer::Draw(const GLsizei count, const GLenum type) const
  {
    assert(bound_ == this && count >= 0);
    glDrawElements(GL_TRIANGLES, count, type, 0);
  }

  IndexBuffer* IndexBuffer::bound_{nullptr};
}
