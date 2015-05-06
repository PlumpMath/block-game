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
    assert(size >= 0 && data != nullptr);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, usage);
  }

  void IndexBuffer::Draw(const GLsizei count, const GLenum type) const
  {
    assert(count >= 0);
    glDrawElements(GL_TRIANGLES, count, type, 0);
  }
}
