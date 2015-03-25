#include "game/block.h"

#include "freeglut/glut.h"

#include "general/vector_2f.h"

namespace block_game
{
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
    static const Vector2F points[] = {{-radius_, -radius_}, {radius_, -radius_}, {radius_, radius_}, {-radius_, radius_}};
    for (Vector2F point : points)
    {
      point.Rotate(rotation_.z);
      glVertex2f(point.x, point.y);
    }
    glEnd();
  }
}
