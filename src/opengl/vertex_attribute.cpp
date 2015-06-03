#include "opengl/vertex_attribute.h"

#include <cassert>
#include <string>

#include <glad/glad.h>

namespace block_game {
VertexAttribute::VertexAttribute(
  const std::string& name,
  const GLint size,
  const GLenum type,
  const GLboolean normalized,
  const GLsizei stride,
  const GLsizeiptr pointer
) :
  name(name),
  size{size},
  type{type},
  normalized{normalized},
  stride{stride},
  pointer{pointer}
{
  assert(0 < size);
  assert(0 <= stride);
}
}
