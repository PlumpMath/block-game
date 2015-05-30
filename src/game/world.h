#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <istream>
#include <vector>

#include "game/grid.h"
#include "general/camera.h"
#include "opengl/program.h"

namespace block_game {
class World {
public:
  World();

  const Camera& GetCamera() const;
  Camera& GetCamera();

  float GetCameraDeltaVertical() const;
  float GetCameraDeltaForward() const;
  float GetCameraDeltaStrafe() const;
  float GetCameraDeltaRoll() const;

  void SetCameraDeltaVertical(float camera_delta_vertical);
  void SetCameraDeltaForward(float camera_delta_forward);
  void SetCameraDeltaStrafe(float camera_delta_strafe);
  void SetCameraDeltaRoll(float camera_delta_roll);

  void Update(double delta);
  void Display(int width, int height);

private:
  void Build(std::istream& stream);

  std::vector<Grid> grids_;

  Camera camera_;
  float camera_delta_vertical_;
  float camera_delta_forward_;
  float camera_delta_strafe_;
  float camera_delta_roll_;

  Program program_;
};
}

#endif
