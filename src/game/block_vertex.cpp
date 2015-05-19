#include "game/block_vertex.h"

#include <cassert>

#include "general/vector.h"

namespace block_game
{
BlockVertex::BlockVertex(const Vector<3>& position, const Vector<3>& normal, const Vector<3>& color)
  : position(position), normal(normal), color(color)
{
  for (size_t i{0}; i < 3; ++i)
  {
    assert(color[i] >= 0.0F);
    assert(color[i] <= 1.0F);
  }
}
}
