#ifndef BLOCK_GAME_GAME_WORLD_H_
#define BLOCK_GAME_GAME_WORLD_H_

#include <istream>
#include <vector>

#include "block_game/game/grid.h"
#include "block_game/general/camera.h"
#include "block_game/opengl/program.h"

namespace block_game {
class World {
public:
  World();

  const Camera& GetCamera() const;
  Camera& GetCamera();

  float GetCameraVerticalSpeed() const;
  float GetCameraForwardSpeed() const;
  float GetCameraStrafeSpeed() const;
  float GetCameraRollSpeed() const;

  void SetCameraVerticalSpeed(float camera_vertical_speed);
  void SetCameraForwardSpeed(float camera_forward_speed);
  void SetCameraStrafeSpeed(float camera_strafe_speed);
  void SetCameraRollSpeed(float camera_roll_speed);

  void Update(double delta_seconds);
  void Display(int screen_width, int screen_height);

private:
  void Build(std::istream& stream);

  std::vector<Grid> grids_;

  Camera camera_;
  float camera_vertical_speed_;
  float camera_forward_speed_;
  float camera_strafe_speed_;
  float camera_roll_speed_;

  Program program_;
};
}

#endif
