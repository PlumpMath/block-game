#include "game/block.h"

#include "freeglut/glut.h"

namespace block_game
{
  const Vector2F Block::points_[] = {{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

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
    rotation_.z += 0.01F;
  }

  void Block::Draw() const
  {
    glBegin(GL_QUADS);
    glColor3f(color_.r, color_.g, color_.b);
    for (Vector2F point : points_)
    {
      point.x *= radius_;
      point.y *= radius_;

      point.Rotate(rotation_.z);

      point.x += position_.x;
      point.y += position_.y;

      glVertex2f(point.x, point.y);
    }
    glEnd();
  }
}
