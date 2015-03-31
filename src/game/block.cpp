#include "game/block.h"

#include "glew/glew.h"

#include "general/matrix_3f.h"
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
    // Bottom
    0, 2, 3,
    3, 1, 0,
    // Top
    6, 4, 5,
    5, 7, 6,
    // South
    4, 0, 1,
    1, 5, 4,
    // West
    6, 2, 0,
    0, 4, 6,
    // East
    5, 1, 3,
    3, 7, 5,
    // North
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
    Matrix3F rotation;
    rotation.RotateY(rotation_.y);
    rotation.RotateX(rotation_.x);
    rotation.RotateZ(rotation_.z);

    program.SetUniformFloat("radius", radius_);
    program.SetUniformVector3F("color", {color_.r, color_.g, color_.b});
    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3F("rotation", rotation);

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
