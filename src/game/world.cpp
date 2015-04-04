#include "game/world.h"

#include <cmath>

#include "glew/glew.h"

#include "general/matrix.h"
#include "shader/vertex.h"
#include "shader/fragment.h"

namespace block_game
{
  World::World() : vertex_shader_(GL_VERTEX_SHADER, vertex_glsl), fragment_shader_(GL_FRAGMENT_SHADER, fragment_glsl),
    program_(vertex_shader_, fragment_shader_)
  {
    blocks_.emplace_back(0.5F, Color3F(1.0F, 0.0F, 0.0F));
    blocks_.emplace_back(0.5F, Color3F(0.0F, 1.0F, 0.0F));
    blocks_.emplace_back(0.5F, Color3F(0.0F, 0.0F, 1.0F));

    const float tau = 8.0F * atan(1.0F);
    const float distance = 0.375F;

    for (size_t i = 0; i < blocks_.size(); ++i)
    {
      blocks_.at(i).position().x = distance * cos((i / (float) blocks_.size()) * tau);
      blocks_.at(i).position().y = distance * sin((i / (float) blocks_.size()) * tau);
    }
  }

  void World::Update(const double delta)
  {
    for (Block& block : blocks_)
    {
      block.Update(delta);
    }
  }

  void World::Display(const int width, const int height)
  {
    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    program_.Bind();

    Matrix<4> view_projection;

    if (width > height)
    {
      view_projection[0][0] = height / (float) width;
    }
    else
    {
      view_projection[1][1] = width / (float) height;
    }

    program_.SetUniformMatrix4("viewProjection", view_projection);

    for (const Block& block : blocks_)
    {
      block.Draw(program_);
    }

    Program::Unbind();

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
  }
}
