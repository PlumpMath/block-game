#include "game/world.h"

#include <cassert>
#include <exception>
#include <fstream>
#include <iostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <json/json.h>

#include "general/camera.h"
#include "general/vector.h"
#include "opengl/program.h"
#include "shader/shaders.h"

namespace {
const std::string world_json{
#include "game/world.json.txt"
};

const std::string world_filename{"world.json"};

const block_game::Vector<3> background_color{0.5F, 0.5F, 1.0F};
}

namespace block_game {
World::World() :
  camera_vertical_speed_{0.0F},
  camera_forward_speed_{0.0F},
  camera_strafe_speed_{0.0F},
  camera_roll_speed_{0.0F},

  program_{program_vert, program_frag}
{
  try {
    Build(std::ifstream{world_filename});
  } catch (const std::exception& exception) {
    std::cerr << "Failed to load " << world_filename << ": " << exception.what() << std::endl;
    std::cerr << std::endl;

    grids_.clear();
    Build(std::istringstream{world_json});
  }
}

const Camera& World::GetCamera() const {
  return camera_;
}

Camera& World::GetCamera() {
  return camera_;
}

float World::GetCameraVerticalSpeed() const {
  return camera_vertical_speed_;
}

float World::GetCameraForwardSpeed() const {
  return camera_forward_speed_;
}

float World::GetCameraStrafeSpeed() const {
  return camera_strafe_speed_;
}

float World::GetCameraRollSpeed() const {
  return camera_roll_speed_;
}

void World::SetCameraVerticalSpeed(const float camera_vertical_speed) {
  camera_vertical_speed_ = camera_vertical_speed;
}

void World::SetCameraForwardSpeed(const float camera_forward_speed) {
  camera_forward_speed_ = camera_forward_speed;
}

void World::SetCameraStrafeSpeed(const float camera_strafe_speed) {
  camera_strafe_speed_ = camera_strafe_speed;
}

void World::SetCameraRollSpeed(const float camera_roll_speed) {
  camera_roll_speed_ = camera_roll_speed;
}

void World::Update(const double delta_seconds) {
  assert(0.0 <= delta_seconds);

  if (0.0 < delta_seconds) {
    for (auto& grid : grids_) {
      grid.Update(delta_seconds);
    }

    Vector<3> camera_delta_vertical{0.0F, 0.0F, 1.0F};
    camera_delta_vertical *= static_cast<float>(camera_vertical_speed_ * delta_seconds);

    Vector<3> camera_delta_forward{0.0F, -1.0F, 0.0F};
    camera_delta_forward.RotateAboutZ(camera_.GetYaw());
    camera_delta_forward *= static_cast<float>(camera_forward_speed_ * delta_seconds);

    Vector<3> camera_delta_strafe{1.0F, 0.0F, 0.0F};
    camera_delta_strafe.RotateAboutZ(camera_.GetYaw());
    camera_delta_strafe *= static_cast<float>(camera_strafe_speed_ * delta_seconds);

    camera_.SetPosition(camera_.GetPosition() + camera_delta_vertical + camera_delta_forward + camera_delta_strafe);
    camera_.SetRoll(camera_.GetRoll() + static_cast<float>(camera_roll_speed_ * delta_seconds));
  }
}

void World::Display(const int screen_width, const int screen_height) {
  assert(0 <= screen_width);
  assert(0 <= screen_height);

  if (0 < screen_width && 0 < screen_height) {
    glViewport(0, 0, screen_width, screen_height);
    glClearColor(background_color[0], background_color[1], background_color[2], 1.0F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    camera_.SetAspectRatio(screen_width / static_cast<float>(screen_height));
    program_.SetUniformMatrix4("u_ViewProjection", camera_.GetMatrix());

    for (auto& grid : grids_) {
      grid.Draw(program_);
    }

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
  }
}

void World::Build(std::istream& stream) {
  Json::Value root;
  stream >> root;

  for (const auto& grid : root["grids"]) {
    grids_.emplace_back(grid);
    grids_.back().RebuildDraw();
  }

  camera_ = root["camera"];
}
}
