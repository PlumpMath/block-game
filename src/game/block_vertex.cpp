#include "game/block_vertex.h"

namespace block_game
{
  BlockVertex::BlockVertex()
  {}

  BlockVertex::BlockVertex(const Vector3F& position, const Vector3F& normal) : position(position), normal(normal)
  {}
}
