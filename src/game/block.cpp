#include "game/block.h"

#include "freeglut/glut.h"

namespace block_game
{
  const Vector3F Block::points_[] = {{-1, -1, 0}, {1, -1, 0}, {1, 1, 0}, {-1, 1, 0}};

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

  void Block::Update()
  {
    rotation_ += {0.01F, 0.01F, 0.01F};
  }

  void Block::Draw() const
  {
    glBegin(GL_QUADS);
    glColor3f(color_.r, color_.g, color_.b);
    for (Vector3F point : points_)
    {
      point *= radius_;
      // Assume the positive y-axis is "forward"
      point.RotateY(rotation_.y); // Roll
      point.RotateX(rotation_.x); // Pitch
      point.RotateZ(rotation_.z); // Yaw
      point += position_;
      glVertex2f(point.x, point.y);
    }
    glEnd();
  }
}
