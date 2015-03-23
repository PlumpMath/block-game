#include "world.h"

#include <cmath>

#include "freeglut/glut.h"

namespace block_game
{
  World::World() : angle_(0)
  {
  }

  void World::Update()
  {
    angle_ += 0.01f;
    glutPostRedisplay();
  }

  void World::Display() const
  {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0f);
    static const float points[][2] = {{-0.5f, -0.5f}, {0.5f, -0.5f}, {0.5f, 0.5f}, {-0.5f, 0.5f}};
    for (const float* point : points)
    {
      glVertex2f(point[0] * cos(angle_) - point[1] * sin(angle_), point[0] * sin(angle_) + point[1] * cos(angle_));
    }
    glEnd();

    glFlush();
  }
}
