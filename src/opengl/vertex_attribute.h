#ifndef BLOCK_GAME_OPENGL_VERTEX_ATTRIBUTE_H_
#define BLOCK_GAME_OPENGL_VERTEX_ATTRIBUTE_H_

#include <string>

#include <glad/glad.h>

namespace block_game
{
  struct VertexAttribute
  {
    VertexAttribute(const std::string&, const GLint, const GLenum, const GLboolean, const GLsizei, const GLsizeiptr);

    std::string name;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLsizeiptr pointer;
  };
}

#endif
