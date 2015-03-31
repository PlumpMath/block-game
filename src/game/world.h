#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <vector>

#include "game/block.h"
#include "opengl/shader.h"
#include "opengl/program.h"

namespace block_game
{
  class World
  {
  public:
    World();

    void Update(const double);
    void Display();

  private:
    std::vector<Block> blocks_;

    const Shader vertex_shader_;
    const Shader fragment_shader_;
    Program program_;
  };
}

#endif
