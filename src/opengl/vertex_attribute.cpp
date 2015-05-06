#include "opengl/vertex_attribute.h"

namespace block_game
{
  VertexAttribute::VertexAttribute(GLuint index, GLint size, GLenum type,
    GLboolean normalized, GLsizei stride, GLsizeiptr pointer)
    : index{index}, size{size}, type{type}, normalized{normalized}, stride{stride}, pointer{pointer}
  {}
}
