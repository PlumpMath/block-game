#include "game/world.h"

#include <cmath>
#include <vector>

#include <glad/glad.h>

#include "general/camera.h"
#include "general/color_3f.h"
#include "general/math.h"
#include "general/vector_2f.h"
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
    grids_.reserve(3);
    grids_.emplace_back(1.0F);
    grids_.emplace_back(1.0F);
    grids_.emplace_back(1.0F);

    for (size_t i = 0; i < grids_.size(); ++i)
    {
      grids_[i].position().x = cos((i / static_cast<float>(grids_.size())) * 2 * kPiF);
      grids_[i].position().y = sin((i / static_cast<float>(grids_.size())) * 2 * kPiF);
      grids_[i].root().color()[i] = 1.0F;
      grids_[i].root().Split();
      grids_[i].root().Child(1, 0, 0)->color().r = 1.0F;
      grids_[i].root().Child(1, 0, 0)->color().g = 1.0F;
      grids_[i].root().Child(1, 0, 0)->color().b = 1.0F;
      grids_[i].RebuildDraw();
    }

    camera_.position().z = -10.0F;
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
    for (Grid& grid : grids_)
    {
      grid.Update(delta);
    }

    Vector2F camera_forward_direction{0.0F, -1.0F};
    Vector2F camera_strafe_direction{1.0F, 0.0F};
    camera_forward_direction.Rotate(camera_.yaw());
    camera_strafe_direction.Rotate(camera_.yaw());

    camera_.position().x += static_cast<float>(camera_delta_forward_ * camera_forward_direction.x * delta);
    camera_.position().y += static_cast<float>(camera_delta_forward_ * camera_forward_direction.y * delta);

    camera_.position().x += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction.x * delta);
    camera_.position().y += static_cast<float>(camera_delta_strafe_ * camera_strafe_direction.y * delta);

    camera_.position().z += static_cast<float>(camera_delta_vertical_ * delta);

    camera_.set_roll(static_cast<float>(camera_.roll() + camera_delta_roll_ * delta));
  }

  void World::Display(const int width, const int height)
  {
    glViewport(0, 0, width, height);
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
