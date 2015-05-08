#include "opengl/buffer.h"

#include <cassert>
#include <vector>

#include <glad/glad.h>

#include "opengl/vertex_attribute.h"

namespace block_game
{
  Buffer::Buffer(const GLenum target, const GLsizeiptr size, const GLenum usage) : target_{target}, usage_{usage}
  {
    glGenBuffers(1, &id_);
    Resize(size);
  }

  Buffer::~Buffer()
  {
    glDeleteBuffers(1, &id_);
  }

  Buffer::Buffer(const Buffer& buffer) : Buffer{buffer.target_, buffer.size_, buffer.usage_}
  {
    if (size_ > 0)
    {
      std::vector<char> data(size_);
      glBindBuffer(target_, buffer.id_);
      glGetBufferSubData(target_, 0, size_, &data[0]);
      glBindBuffer(target_, 0);
      SetData(&data[0]);
    }
  }

  Buffer& Buffer::operator=(const Buffer& buffer)
  {
    target_ = buffer.target_;
    usage_ = buffer.usage_;
    Resize(buffer.size_);
    if (size_ > 0)
    {
      std::vector<char> data(size_);
      glBindBuffer(target_, buffer.id_);
      glGetBufferSubData(target_, 0, size_, &data[0]);
      glBindBuffer(target_, 0);
      SetData(&data[0]);
    }
    return *this;
  }

  Buffer::Buffer(Buffer&& buffer) : id_{buffer.id_}, target_{buffer.target_}, size_{buffer.size_}, usage_{buffer.usage_}
  {
    buffer.id_ = 0;
  }

  Buffer& Buffer::operator=(Buffer&& buffer)
  {
    id_ = buffer.id_;
    target_ = buffer.target_;
    size_ = buffer.size_;
    usage_ = buffer.usage_;
    buffer.id_ = 0;
    return *this;
  }

  GLenum Buffer::GetTarget() const
  {
    return target_;
  }

  GLsizeiptr Buffer::GetSize() const
  {
    return size_;
  }

  GLenum Buffer::GetUsage() const
  {
    return usage_;
  }

  void Buffer::Resize(const GLsizeiptr size)
  {
    assert(size >= 0);
    size_ = size;
    glBindBuffer(target_, id_);
    glBufferData(target_, size_, nullptr, usage_);
    glBindBuffer(target_, 0);
  }

  void Buffer::SetData(const GLvoid* data)
  {
    assert(data);
    glBindBuffer(target_, id_);
    glBufferSubData(target_, 0, size_, data);
    glBindBuffer(target_, 0);
  }
}