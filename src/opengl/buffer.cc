#include "block_game/opengl/buffer.h"

#include <algorithm>
#include <cassert>
#include <vector>

#include <glad/glad.h>

#include "block_game/opengl/vertex_attribute.h"

namespace block_game {
Buffer::Buffer(const GLenum target, const GLsizeiptr size, const GLenum usage) :
  target_{target},
  size_{size},
  usage_{usage}
{
  glGenBuffers(1, &id_);
  Resize(size_);
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &id_);
}

Buffer::Buffer(const Buffer& buffer) : Buffer{buffer.target_, buffer.size_, buffer.usage_} {
  if (0 < size_) {
    std::vector<char> data(size_);
    glBindBuffer(target_, buffer.id_);
    glGetBufferSubData(target_, 0, size_, &data[0]);
    glBindBuffer(target_, 0);
    SetData(&data[0]);
  }
}

Buffer::Buffer(Buffer&& buffer) :
  id_{buffer.id_},
  target_{buffer.target_},
  size_{buffer.size_},
  usage_{buffer.usage_}
{
  buffer.id_ = 0;
}

Buffer& Buffer::operator=(Buffer buffer) {
  std::swap(id_, buffer.id_);
  std::swap(target_, buffer.target_);
  std::swap(size_, buffer.size_);
  std::swap(usage_, buffer.usage_);
  return *this;
}

GLenum Buffer::GetTarget() const {
  return target_;
}

GLsizeiptr Buffer::GetSize() const {
  return size_;
}

GLenum Buffer::GetUsage() const {
  return usage_;
}

void Buffer::Resize(const GLsizeiptr size) {
  size_ = size;
  glBindBuffer(target_, id_);
  glBufferData(target_, size_, nullptr, usage_);
  glBindBuffer(target_, 0);
}

void Buffer::SetData(const GLvoid* const data) {
  assert(data != nullptr);

  glBindBuffer(target_, id_);
  glBufferSubData(target_, 0, size_, data);
  glBindBuffer(target_, 0);
}
}
