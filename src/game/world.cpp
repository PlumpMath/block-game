#include "game/world.h"

#include <exception>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <glad/glad.h>
#include <json/json.h>

#include "general/camera.h"
#include "general/vector.h"
#include "opengl/program.h"
#include "shader/shaders.h"

namespace
{
  const std::string world_json{
#include "game/world.json.txt"
  };
}

namespace block_game
{
  World::World() : camera_delta_vertical_{0.0F}, camera_delta_forward_{0.0F}, camera_delta_strafe_{0.0F},
    camera_delta_roll_{0.0F},
    program_{program_vert, program_frag}
  {
    Json::Value root;

    std::ifstream file{"world.json"};
    try
    {
      if (!file)
      {
        throw std::exception{"file missing"};
      }
      file >> root;
    }
    catch (const std::exception& exception)
    {
      std::cerr << "Failed to load world.json: " << exception.what() << std::endl;
      std::cerr << std::endl;

      std::istringstream stream{world_json};
      stream >> root;
    }

    for (const auto& grid : root["grids"])
    {
      grids_.emplace_back(grid);
      grids_.back().RebuildDraw();
    }

    camera_ = Camera{root["camera"]};
  }

  const Camera& World::GetCamera() const
  {
    return camera_;
  }

  Camera& World::GetCamera()
  {
    return camera_;
  }

  float World::GetCameraDeltaVertical() const
  {
    return camera_delta_vertical_;
  }

  float World::GetCameraDeltaForward() const
  {
    return camera_delta_forward_;
  }

  float World::GetCameraDeltaStrafe() const
  {
    return camera_delta_strafe_;
  }

  float World::GetCameraDeltaRoll() const
  {
    return camera_delta_roll_;
  }

  void World::SetCameraDeltaVertical(const float camera_delta_vertical)
  {
    camera_delta_vertical_ = camera_delta_vertical;
  }

  void World::SetCameraDeltaForward(const float camera_delta_forward)
  {
    camera_delta_forward_ = camera_delta_forward;
  }

  void World::SetCameraDeltaStrafe(const float camera_delta_strafe)
  {
    camera_delta_strafe_ = camera_delta_strafe;
  }

  void World::SetCameraDeltaRoll(const float camera_delta_roll)
  {
    camera_delta_roll_ = camera_delta_roll;
  }

  void World::Update(const double delta)
  {
    assert(delta >= 0.0);
    if (delta > 0.0)
    {
      for (auto& grid : grids_)
      {
        grid.Update(delta);
      }

      Vector<2> camera_forward_direction{0.0F, -1.0F};
      Vector<2> camera_strafe_direction{1.0F, 0.0F};
      camera_forward_direction.RotateZ(camera_.GetYaw());
      camera_strafe_direction.RotateZ(camera_.GetYaw());

      Vector<3> camera_position = camera_.GetPosition();
      camera_position[0] += static_cast<float>(camera_delta_forward_ * camera_forward_direction[0] * delta);
      camera_position[1] += static_cast<float>(camera_delta_forward_ * camera_forward_direction[1] * delta);

      camera_position[0] += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction[0] * delta);
      camera_position[1] += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction[1] * delta);

      camera_position[2] += static_cast<float>(camera_delta_vertical_ * delta);
      camera_.SetPosition(camera_position);

      camera_.SetRoll(static_cast<float>(camera_.GetRoll() + camera_delta_roll_ * delta));
    }
  }

  void World::Display(const int width, const int height)
  {
    assert(width >= 0 && height >= 0);
    if (width > 0 && height > 0)
    {
      glViewport(0, 0, width, height);
      glClearColor(0.5F, 0.5F, 1.0F, 1.0F);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      glEnable(GL_CULL_FACE);
      glEnable(GL_DEPTH_TEST);

      camera_.SetAspectRatio(width / static_cast<float>(height));
      program_.SetUniformMatrix4("viewProjection", camera_.GetMatrix());

      for (auto& grid : grids_)
      {
        grid.Draw(program_);
      }

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
    }
  }
}
