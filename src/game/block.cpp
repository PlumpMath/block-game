#include "game/block.h"

#include <glad/glad.h>

#include "general/color_3f.h"
#include "general/matrix.h"
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

  Block::Block(const float radius, const Color3F& color) : radius_{radius}, color_{color}
  {
    vertex_buffer_.Bind();
    vertex_buffer_.SetData(sizeof vertices_, vertices_, GL_STATIC_DRAW);
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.SetData(sizeof indices_, indices_, GL_STATIC_DRAW);
    IndexBuffer::Unbind();
  }

  float Block::radius() const
  {
    return radius_;
  }

  const Color3F& Block::color() const
  {
    return color_;
  }

  const Vector3F& Block::position() const
  {
    return position_;
  }

  const Vector3F& Block::rotation() const
  {
    return rotation_;
  }

  Vector3F& Block::position()
  {
    return position_;
  }

  Vector3F& Block::rotation()
  {
    return rotation_;
  }

  void Block::Update(const double delta)
  {
    position_.RotateZ(static_cast<float>(delta));

    rotation_.x += static_cast<float>((1 - color_.r) * delta);
    rotation_.y += static_cast<float>((1 - color_.g) * delta);
    rotation_.z += static_cast<float>((1 - color_.b) * delta);
  }

  void Block::Draw(Program& program) const
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_.y);
    rotation.RotateX(rotation_.x);
    rotation.RotateZ(rotation_.z);

    program.SetUniformFloat("radius", radius_);
    program.SetUniformVector3F("color", {color_.r, color_.g, color_.b});
    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    vertex_buffer_.Bind();
    glVertexAttribPointer(0, Vector3F::kDimensions, GL_FLOAT, GL_TRUE, 2 * sizeof(Vector3F), 0);
    glVertexAttribPointer(1, Vector3F::kDimensions, GL_FLOAT, GL_TRUE, 2 * sizeof(Vector3F), (void*) sizeof(Vector3F));
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.Draw(sizeof indices_, GL_UNSIGNED_BYTE);
    IndexBuffer::Unbind();
  }
}
