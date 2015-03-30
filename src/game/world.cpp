#include "game/world.h"

#include "glew/glew.h"

namespace block_game
{
  World::World()
  {
    blocks_.push_back(Block(0.5F, Color3F(1.0F, 1.0F, 1.0F)));
  }

  void World::Update(const double delta)
  {
    for (Block& block : blocks_)
    {
      block.Update(delta);
    }
  }

  void World::Display() const
  {
    glClear(GL_COLOR_BUFFER_BIT);
    for (const Block& block : blocks_)
    {
      block.Draw();
    }
  }
}
