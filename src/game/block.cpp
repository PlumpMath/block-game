#include "game/block.h"

#include <glad/glad.h>

#include "general/color_3f.h"
#include "general/vector_3f.h"
#include "opengl/index_buffer.h"
#include "opengl/program.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  const Vector3F Block::vertices_[][2]
  {
    // -x
    {{-1.0F, -1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, 1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, -1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, 1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}},
    // +x
    {{1.0F, -1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, 1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, -1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, 1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},
    // -y
    {{-1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}},
    {{-1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},
    // +y
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},
    // -z
    {{-1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    // +z
    {{-1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}}
  };
  const unsigned char Block::indices_[]
  {
    // -x
    0, 1, 3,
      0, 3, 2,
      // +x
      4, 6, 7,
      4, 7, 5,
      // -y
      8, 10, 11,
      8, 11, 9,
      // +y
      12, 13, 15,
      12, 15, 14,
      // -z
      16, 17, 19,
      16, 19, 18,
      // +z
      20, 22, 23,
      20, 23, 21
  };

  Block::Block(const Block* parent, const float radius, const Vector3F& position)
    : parent_{parent}, radius_{radius}, position_{position}, is_leaf_{true}
  {
    Vector3F vertices[24][2];
    for (int i = 0; i < 24; ++i)
    {
      vertices[i][0] = position + radius * vertices_[i][0];
      vertices[i][1] = vertices_[i][1];
    }

    vertex_buffer_.Bind();
    vertex_buffer_.SetData(sizeof vertices, vertices, GL_STATIC_DRAW);
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.SetData(sizeof indices_, indices_, GL_STATIC_DRAW);
    IndexBuffer::Unbind();
  }

  const Block* Block::parent() const
  {
    return parent_;
  }

  float Block::radius() const
  {
    return radius_;
  }

  const Vector3F& Block::position() const
  {
    return position_;
  }

  bool Block::is_leaf() const
  {
    return is_leaf_;
  }

  const Block* Block::Child(const int x, const int y, const int z) const
  {
    return children[z][y][x];
  }

  const Color3F& Block::color() const
  {
    return color_;
  }

  Color3F& Block::color()
  {
    return color_;
  }

  void Block::Draw(Program& program) const
  {
    program.SetUniformVector3F("color", {color_.r, color_.g, color_.b});

    vertex_buffer_.Bind();
    glVertexAttribPointer(0, Vector3F::kDimensions, GL_FLOAT, GL_TRUE, 2 * sizeof(Vector3F), 0);
    glVertexAttribPointer(1, Vector3F::kDimensions, GL_FLOAT, GL_TRUE, 2 * sizeof(Vector3F), (void*) sizeof(Vector3F));
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.Draw(sizeof indices_, GL_UNSIGNED_BYTE);
    IndexBuffer::Unbind();
  }
}
