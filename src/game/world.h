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

    void set_camera_delta_yaw(const float);
    void set_camera_delta_pitch(const float);
    void set_camera_delta_roll(const float);

    void Update(const double);
    void Display(const int, const int);

  private:
    std::vector<Block> blocks_;

    Camera camera_;
    float camera_delta_yaw_;
    float camera_delta_pitch_;
    float camera_delta_roll_;

    const Shader vertex_shader_;
    const Shader fragment_shader_;
    Program program_;
  };
}

#endif
