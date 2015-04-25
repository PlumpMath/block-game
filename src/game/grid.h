#ifndef BLOCK_GAME_GAME_GRID_H_
#define BLOCK_GAME_GAME_GRID_H_

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
    Grid(const float, const Color3F&);

    const Vector3F& position() const;
    const Vector3F& rotation() const;

    Vector3F& position();
    Vector3F& rotation();

    void Update(const double);
    void Draw(Program&) const;

  private:
    Vector3F position_;
    Vector3F rotation_;

    Block root_;
  };
}

#endif
