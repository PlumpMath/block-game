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
  }

  void World::Update(const double delta)
  {
    for (Block& block : blocks_)
    {
      block.Update(delta);
    }
  }

  void World::Display()
  {
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    program_.Use();

    for (const Block& block : blocks_)
    {
      Matrix4F rotation;
      rotation.RotateY(block.rotation().y);
      rotation.RotateX(block.rotation().x);
      rotation.RotateZ(block.rotation().z);

      program_.SetUniformFloat("radius", block.radius());
      program_.SetUniformVector3F("color", {block.color().r, block.color().g, block.color().b});
      program_.SetUniformVector3F("position", block.position());
      program_.SetUniformMatrix4F("rotation", rotation);

      block.Draw();
    }

    glUseProgram(0);
    glDisable(GL_CULL_FACE);
  }
}
