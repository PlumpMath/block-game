#include "game/world.h"

#include "freeglut/glut.h"

namespace block_game
{
  World::World() : block_(0.5F, Color3D(1.0F, 1.0F, 1.0F))
  {
  }

  void World::Update()
  {
    block_.Update();
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
