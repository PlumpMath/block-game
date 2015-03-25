#include "game/world.h"

#include "freeglut/glut.h"

namespace block_game
{
  World::World()
  {
    blocks_.push_back(Block(0.5F, Color3F(1.0F, 1.0F, 1.0F)));
  }

  void World::Update()
  {
    for (Block& block : blocks_)
    {
      block.Update();
    }
    glutPostRedisplay();
  }

  void World::Display() const
  {
    glClearColor(0.0F, 0.0F, 0.0F, 1.0F);
    glClear(GL_COLOR_BUFFER_BIT);
    for (const Block& block : blocks_)
    {
      block.Draw();
    }
    glFlush();
  }
}
