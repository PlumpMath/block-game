#ifndef BLOCK_GAME_OPENGL_VERTEX_ATTRIBUTE_H_
#define BLOCK_GAME_OPENGL_VERTEX_ATTRIBUTE_H_

#include <glad/glad.h>

namespace block_game
{
  struct VertexAttribute
  {
    VertexAttribute(GLuint, GLint, GLenum, GLboolean, GLsizei, GLsizeiptr);

    GLuint index;
    GLint size;
    GLenum type;
    GLboolean normalized;
    GLsizei stride;
    GLsizeiptr pointer;
  };
}

#endif
