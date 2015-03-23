#include "block.h"

#include <cmath>

#include "freeglut/glut.h"

namespace block_game
{
  Block::Block(const float radius, const Vector3D& position, const Vector3D& rotation)
    : radius_(radius), position_(position), rotation_(rotation)
  {
  }

  const float Block::radius() const
  {
    return radius_;
  }

  const Vector3D& Block::position() const
  {
    return position_;
  }

  const Vector3D& Block::rotation() const
  {
    return rotation_;
  }

  void Block::Draw() const
  {
    glBegin(GL_QUADS);
    glColor3f(1.0F, 0.0F, 0.0F);
    static const float points[][2] = {{-radius_, -radius_}, {radius_, -radius_}, {radius_, radius_}, {-radius_, radius_}};
    for (const float* point : points)
    {
      glVertex2f(point[0] * cos(rotation_.z) - point[1] * sin(rotation_.z), point[0] * sin(rotation_.z) + point[1] * cos(rotation_.z));
    }
    glEnd();
  }
}
