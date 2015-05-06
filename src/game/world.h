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

    const Camera& GetCamera() const;
    Camera& GetCamera();

    float GetCameraDeltaVertical() const;
    float GetCameraDeltaForward() const;
    float GetCameraDeltaStrafe() const;
    float GetCameraDeltaRoll() const;

    void SetCameraDeltaVertical(const float);
    void SetCameraDeltaForward(const float);
    void SetCameraDeltaStrafe(const float);
    void SetCameraDeltaRoll(const float);

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
