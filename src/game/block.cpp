#include "game/block.h"

#include <cmath>

#include "glew/glew.h"

#include "general/matrix.h"
#include "opengl/program.h"

namespace block_game
{
  const Vector3F Block::vertices_[][2] =
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
  const unsigned char Block::indices_[] =
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

  Block::Block(const float radius, const Color3F& color) : radius_(radius), color_(color)
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
    position_.RotateZ((float) delta);

    rotation_.x += (1 - color_.r) * (float) delta;
    rotation_.y += (1 - color_.g) * (float) delta;
    rotation_.z += (1 - color_.b) * (float) delta;
  }

  void Block::Draw(Program& program) const
  {
    const float sine_x = sin(rotation_.x);
    const float cosine_x = cos(rotation_.x);

    const float sine_y = sin(rotation_.y);
    const float cosine_y = cos(rotation_.y);

    const float sine_z = sin(rotation_.z);
    const float cosine_z = cos(rotation_.z);

    Matrix<3> rotation_x;
    rotation_x[1][1] = cosine_x;
    rotation_x[1][2] = -sine_x;
    rotation_x[2][1] = sine_x;
    rotation_x[2][2] = cosine_x;

    Matrix<3> rotation_y;
    rotation_y[0][0] = cosine_y;
    rotation_y[0][2] = sine_y;
    rotation_y[2][0] = -sine_y;
    rotation_y[2][2] = cosine_y;

    Matrix<3> rotation_z;
    rotation_z[0][0] = cosine_z;
    rotation_z[0][1] = -sine_z;
    rotation_z[1][0] = sine_z;
    rotation_z[1][1] = cosine_z;

    program.SetUniformFloat("radius", radius_);
    program.SetUniformVector3F("color", {color_.r, color_.g, color_.b});
    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3("rotation", rotation_z * rotation_x * rotation_y);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    vertex_buffer_.Bind();
    glVertexPointer(Vector3F::kDimensions, GL_FLOAT, 2 * sizeof(Vector3F), (void*) 0);
    glNormalPointer(GL_FLOAT, 2 * sizeof(Vector3F), (void*) sizeof(Vector3F));
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.Draw(36, GL_UNSIGNED_BYTE);
    IndexBuffer::Unbind();

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}
