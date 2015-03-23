#include "world.h"

#include <cmath>

#include "freeglut/glut.h"

namespace block_game
{
  World::World() : angle_(0.0F)
  {
  }

  void World::Update()
  {
    angle_ += 0.01F;
    glutPostRedisplay();
  }

  void World::Display() const
  {
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1.0F, 0.0F, 0.0F);
    static const float points[][2] = {{-0.5F, -0.5F}, {0.5F, -0.5F}, {0.5F, 0.5F}, {-0.5F, 0.5F}};
    for (const float* point : points)
    {
      glVertex2f(point[0] * cos(angle_) - point[1] * sin(angle_), point[0] * sin(angle_) + point[1] * cos(angle_));
    }
    glEnd();

    glFlush();
  }
}
