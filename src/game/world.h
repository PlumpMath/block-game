#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <vector>

#include "game/block.h"
#include "general/camera.h"
#include "opengl/shader.h"
#include "opengl/program.h"

namespace block_game
{
  class World
  {
  public:
    World();

    void Update(const double);
    void Display(const int, const int);

  private:
    std::vector<Block> blocks_;
    Camera camera_;

    const Shader vertex_shader_;
    const Shader fragment_shader_;
    Program program_;
  };
}

#endif
