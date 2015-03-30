#include "game/world.h"

#include "glew/glew.h"

#include "general/matrix_4f.h"
#include "shader/vertex.h"
#include "shader/fragment.h"

namespace block_game
{
  World::World() : vertex_shader_(GL_VERTEX_SHADER, vertex_glsl), fragment_shader_(GL_FRAGMENT_SHADER, fragment_glsl),
    program_(vertex_shader_, fragment_shader_)
  {
    blocks_.push_back(Block(0.5F, Color3F(1.0F, 1.0F, 1.0F)));

    program_.Use();
    program_.SetUniformMatrix4F("matrix", Matrix4F());
    glUseProgram(0);
  }

  void World::Update(const double delta)
  {
    for (Block& block : blocks_)
    {
      block.Update(delta);
    }
  }

  void World::Display() const
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    program_.Use();

    for (const Block& block : blocks_)
    {
      block.Draw();
    }

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
  }
}
