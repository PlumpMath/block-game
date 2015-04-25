#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <vector>

#include "game/grid.h"
#include "general/camera.h"
#include "opengl/program.h"
#include "opengl/shader.h"

namespace block_game
{
  class World
  {
  public:
    World();

    Camera& camera();
    void set_camera_delta_vertical(const float);
    void set_camera_delta_forward(const float);
    void set_camera_delta_strafe(const float);
    void set_camera_delta_roll(const float);

    void Update(const double);
    void Display(const int, const int);

  private:
    std::vector<Grid> grids_;

    Camera camera_;
    float camera_delta_vertical_;
    float camera_delta_forward_;
    float camera_delta_strafe_;
    float camera_delta_roll_;

    const Shader vertex_shader_;
    const Shader fragment_shader_;
    Program program_;
  };
}

#endif
