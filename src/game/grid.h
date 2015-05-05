#ifndef BLOCK_GAME_GAME_GRID_H_
#define BLOCK_GAME_GAME_GRID_H_

#include <glad/glad.h>

#include "game/block.h"
#include "general/vector.h"
#include "opengl/index_buffer.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  class Program;

  class Grid
  {
  public:
    Grid(const float);

    const Vector<3>& position() const;
    const Vector<3>& rotation() const;
    const Block& root() const;

    Vector<3>& position();
    Vector<3>& rotation();
    Block& root();

    void Update(const double);
    void RebuildDraw();
    void Draw(Program&) const;

  private:
    Vector<3> position_;
    Vector<3> rotation_;
    Block root_;

    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    GLsizei num_indices_;
  };
}

#endif
