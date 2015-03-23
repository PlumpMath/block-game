#include "block.h"

#include <cmath>

#include "freeglut/glut.h"

namespace block_game
{
  Block::Block(const float radius, const Color3D& color)
    : radius_(radius), color_(color), position_(), rotation_()
  {
  }

  float Block::radius() const
  {
    return radius_;
  }

  const Color3D& Block::color() const
  {
    return color_;
  }

  Vector3D& Block::position()
  {
    return position_;
  }

  Vector3D& Block::rotation()
  {
    return rotation_;
  }

  void Block::Draw() const
  {
    glBegin(GL_QUADS);
    glColor3f(color_.r, color_.g, color_.b);
    static const float points[][2] = {{-radius_, -radius_}, {radius_, -radius_}, {radius_, radius_}, {-radius_, radius_}};
    for (const float* point : points)
    {
      glVertex2f(point[0] * cos(rotation_.z) - point[1] * sin(rotation_.z), point[0] * sin(rotation_.z) + point[1] * cos(rotation_.z));
    }
    glEnd();
  }
}
