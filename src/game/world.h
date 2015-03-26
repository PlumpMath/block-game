#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <vector>

#include "game/block.h"

namespace block_game
{
  class World
  {
  public:
    World();

    void Update(const double);
    void Display() const;

  private:
    std::vector<Block> blocks_;
  };
}

#endif
