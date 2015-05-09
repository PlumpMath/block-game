#include "game/block_vertex.h"

#include "general/vector.h"

namespace block_game
{
  BlockVertex::BlockVertex(const Vector<3>& position, const Vector<3>& normal, const Vector<3>& color)
    : position(position), normal(normal), color(color)
  {}
}
