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
      grids_[i].position()[0] = cos((i / static_cast<float>(grids_.size())) * 2 * kPiF);
      grids_[i].position()[1] = sin((i / static_cast<float>(grids_.size())) * 2 * kPiF);
      grids_[i].root().set_solid(true);
      grids_[i].root().color()[i] = 1.0F;
      grids_[i].root().Split();
      grids_[i].root().Child(0, 0, 0).set_solid(false);
      grids_[i].root().Child(1, 1, 1).set_solid(false);
      grids_[i].RebuildDraw();
    }

    camera_.position()[2] = -10.0F;
    camera_.set_z_far(100.0F);
  }

  Camera& World::camera()
  {
    return camera_;
  }

  void World::set_camera_delta_vertical(const float camera_delta_vertical)
  {
    camera_delta_vertical_ = camera_delta_vertical;
  }

  void World::set_camera_delta_forward(const float camera_delta_forward)
  {
    camera_delta_forward_ = camera_delta_forward;
  }

  void World::set_camera_delta_strafe(const float camera_delta_strafe)
  {
    camera_delta_strafe_ = camera_delta_strafe;
  }

  void World::set_camera_delta_roll(const float camera_delta_roll)
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
      camera_forward_direction.RotateZ(camera_.yaw());
      camera_strafe_direction.RotateZ(camera_.yaw());

      camera_.position()[0] += static_cast<float>(camera_delta_forward_ * camera_forward_direction[0] * delta);
      camera_.position()[1] += static_cast<float>(camera_delta_forward_ * camera_forward_direction[1] * delta);

      camera_.position()[0] += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction[0] * delta);
      camera_.position()[1] += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction[1] * delta);

      camera_.position()[2] += static_cast<float>(camera_delta_vertical_ * delta);

      camera_.set_roll(static_cast<float>(camera_.roll() + camera_delta_roll_ * delta));
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

      camera_.set_aspect_ratio(width / static_cast<float>(height));
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
