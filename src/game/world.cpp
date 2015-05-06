#include "game/world.h"

#include <cmath>
#include <vector>

#include <glad/glad.h>

#include "general/camera.h"
#include "general/math.h"
#include "general/vector.h"
#include "opengl/program.h"
#include "opengl/shader.h"
#include "shader/fragment.h"
#include "shader/vertex.h"

namespace block_game
{
  World::World() : camera_delta_vertical_{0.0F}, camera_delta_forward_{0.0F}, camera_delta_strafe_{0.0F},
    camera_delta_roll_{0.0F},
    vertex_shader_{GL_VERTEX_SHADER, vertex_glsl},
    fragment_shader_{GL_FRAGMENT_SHADER, fragment_glsl},
    program_{vertex_shader_, fragment_shader_}
  {
    grids_.emplace_back(1.0F);
    grids_.emplace_back(1.0F);
    grids_.emplace_back(1.0F);

    for (size_t i = 0; i < grids_.size(); ++i)
    {
      Grid& grid = grids_[i];
      grid.SetPosition({cos((i / static_cast<float>(grids_.size())) * 2 * kPiF),
        sin((i / static_cast<float>(grids_.size())) * 2 * kPiF),
        0.0F});

      Block& root = grid.GetRoot();
      root.SetSolid(true);

      Vector<3> root_color = root.GetColor();
      root_color[i] = 1.0F;
      root.SetColor(root_color);

      root.Split();
      root.GetChild(0, 0, 0).SetSolid(false);
      root.GetChild(1, 1, 1).SetSolid(false);

      grid.RebuildDraw();
    }

    camera_.SetPosition({0.0F, 0.0F, -10.0F});
    camera_.SetZFar(100.0F);
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
      for (Grid& grid : grids_)
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

      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      program_.Bind();

      camera_.SetAspectRatio(width / static_cast<float>(height));
      program_.SetUniformMatrix4("viewProjection", camera_.GetMatrix());

      for (const Grid& grid : grids_)
      {
        grid.Draw(program_);
      }

      Program::Unbind();

      glDisableVertexAttribArray(2);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(0);

      glDisable(GL_DEPTH_TEST);
      glDisable(GL_CULL_FACE);
    }
  }
}
