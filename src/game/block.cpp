#include "game/block.h"

#include "glfw/glfw3.h"

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
  const int Block::indices_[] =
  {
    // Bottom
    0, 1, 2,
    1, 2, 3,
    // Top
    4, 5, 6,
    5, 6, 7,
    // South
    0, 1, 4,
    1, 4, 5,
    // West
    0, 2, 4,
    2, 4, 6,
    // East
    1, 3, 5,
    3, 5, 7,
    // North
    2, 3, 6,
    3, 6, 7
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
    for (const int index : indices_)
    {
      Vector3F vertex = vertices_[index];
      vertex *= radius_;
      // Assume the positive y-axis is "forward"
      vertex.RotateY(rotation_.y); // Roll
      vertex.RotateX(rotation_.x); // Pitch
      vertex.RotateZ(rotation_.z); // Yaw
      vertex += position_;
      glVertex2f(vertex.x, vertex.y);
    }
    glEnd();
  }
}
