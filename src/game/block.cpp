#include "game/block.h"

#include <cmath>

#include "glew/glew.h"

#include "general/matrix.h"
#include "opengl/program.h"

namespace block_game
{
  const Vector3F Block::vertices_[] =
  {
    {-1.0F, -1.0F, -1.0F},
    {1.0F, -1.0F, -1.0F},
    {-1.0F, 1.0F, -1.0F},
    {1.0F, 1.0F, -1.0F},
    {-1.0F, -1.0F, 1.0F},
    {1.0F, -1.0F, 1.0F},
    {-1.0F, 1.0F, 1.0F},
    {1.0F, 1.0F, 1.0F}
  };
  const Vector3F Block::normals_[] =
  {
    {0.0F, 0.0F, -1.0F},
    {0.0F, 0.0F, 1.0F},
    {0.0F, -1.0F, 0.0F},
    {-1.0F, 0.0F, 0.0F},
    {1.0F, 0.0F, 0.0F},
    {0.0F, 1.0F, 0.0F}
  };
  const int Block::indices_[] =
  {
    // -z
    0, 2, 3,
    3, 1, 0,
    // +z
    6, 4, 5,
    5, 7, 6,
    // -y
    4, 0, 1,
    1, 5, 4,
    // -x
    6, 2, 0,
    0, 4, 6,
    // +x
    5, 1, 3,
    3, 7, 5,
    // +y
    7, 3, 2,
    2, 6, 7
  };

  Block::Block(const float radius, const Color3F& color) : radius_(radius), color_(color)
  {}

  void Block::Update(const double delta)
  {
    rotation_.x += (float) delta;
    rotation_.y += (float) delta;
    rotation_.z += (float) delta;
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

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < 6; ++i)
    {
      const Vector3F& normal = normals_[i];
      glNormal3f(normal.x, normal.y, normal.z);

      for (int j = 6 * i; j < 6 * (i + 1); ++j)
      {
        const Vector3F& vertex = vertices_[indices_[j]];
        glVertex3f(vertex.x, vertex.y, vertex.z);
      }
    }

    glEnd();
  }
}
