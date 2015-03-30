#include "game/block.h"

#include "glew/glew.h"

namespace block_game
{
  const Vector3F Block::vertices_[] =
  {
    {-1, -1, -1},
    {1, -1, -1},
    {-1, 1, -1},
    {1, 1, -1},
    {-1, -1, 1},
    {1, -1, 1},
    {-1, 1, 1},
    {1, 1, 1}
  };
  const Vector3F Block::normals_[] =
  {
    {0, 0, -1},
    {0, 0, 1},
    {0, -1, 0},
    {-1, 0, 0},
    {1, 0, 0},
    {0, 1, 0}
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

  float Block::radius() const
  {
    return radius_;
  }

  const Color3F& Block::color() const
  {
    return color_;
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
    rotation_.x += (float) delta;
    rotation_.y += (float) delta;
    rotation_.z += (float) delta;
  }

  void Block::Draw() const
  {
    glBegin(GL_TRIANGLES);
    glColor3f(color_.r, color_.g, color_.b);
    for (int i = 0; i < 6; ++i)
    {
      Vector3F normal = normals_[i];
      // Assume the positive y-axis is "forward"
      normal.RotateY(rotation_.y); // Roll
      normal.RotateX(rotation_.x); // Pitch
      normal.RotateZ(rotation_.z); // Yaw
      glNormal3f(normal.x, normal.y, normal.z);
      for (int j = 6 * i; j < 6 * (i + 1); ++j)
      {
        Vector3F vertex = vertices_[indices_[j]];
        vertex *= radius_;
        // Assume the positive y-axis is "forward"
        vertex.RotateY(rotation_.y); // Roll
        vertex.RotateX(rotation_.x); // Pitch
        vertex.RotateZ(rotation_.z); // Yaw
        vertex += position_;
        glVertex2f(vertex.x, vertex.y);
      }
    }
    glEnd();
  }
}
