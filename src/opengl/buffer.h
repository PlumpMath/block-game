#ifndef BLOCK_GAME_OPENGL_BUFFER_H_
#define BLOCK_GAME_OPENGL_BUFFER_H_

#include <vector>

#include <glad/glad.h>

#include "opengl/program.h"
#include "opengl/vertex_attribute.h"

namespace block_game
{
class Buffer
{
public:
  Buffer(GLenum target, GLsizeiptr size, GLenum usage);
  ~Buffer();
  Buffer(const Buffer& buffer);
  Buffer(Buffer&& buffer);
  Buffer& operator=(Buffer buffer);

  GLenum GetTarget() const;
  GLsizeiptr GetSize() const;
  GLenum GetUsage() const;

  void Resize(GLsizeiptr size);
  void SetData(const GLvoid* data);

  friend void Program::Draw(const Buffer& vertex_buffer, const Buffer& index_buffer,
    const std::vector<VertexAttribute>& attributes) const;

private:
  GLuint id_;
  GLenum target_;
  GLsizeiptr size_;
  GLenum usage_;
};
}

#endif
