#include "world.h"

#include "freeglut/glut.h"

namespace block_game
{
  World::World() : block_(0.5F, Vector3D(0.0F, 0.0F, 0.0F), Vector3D(0.0F, 0.0F, 0.0F))
  {
  }

  void World::Update()
  {
    block_.rotation().z += 0.01;
    glutPostRedisplay();
  }

  void World::Display() const
  {
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    block_.Draw();
    glFlush();
  }
}
