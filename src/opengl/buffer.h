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
    Buffer(const GLenum, const GLsizeiptr, const GLenum);
    ~Buffer();

    Buffer(const Buffer&);
    Buffer& operator=(const Buffer&);

    Buffer(Buffer&&);
    Buffer& operator=(Buffer&&);

    GLenum GetTarget() const;
    GLsizeiptr GetSize() const;
    GLenum GetUsage() const;

    void Resize(GLsizeiptr);
    void SetData(const GLvoid*);

    friend void Program::Draw(const Buffer&, const Buffer&, const std::vector<const VertexAttribute>&);

  private:
    GLuint id_;
    GLenum target_;
    GLsizeiptr size_;
    GLenum usage_;
  };
}

#endif
