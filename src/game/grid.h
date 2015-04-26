#ifndef BLOCK_GAME_GAME_GRID_H_
#define BLOCK_GAME_GAME_GRID_H_

#include <glad/glad.h>

#include "game/block.h"
#include "general/color_3f.h"
#include "general/vector_3f.h"
#include "opengl/index_buffer.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  class Program;

  class Grid
  {
  public:
    Grid(const float);

    const Vector3F& position() const;
    const Vector3F& rotation() const;
    const Block& root() const;

    Vector3F& position();
    Vector3F& rotation();
    Block& root();

    void Update(const double);
    void Draw(Program&) const;

  private:
    Vector3F position_;
    Vector3F rotation_;
    Block root_;

    VertexBuffer vertex_buffer_;
    IndexBuffer index_buffer_;
    GLsizei num_indices_;
  };
}

#endif
