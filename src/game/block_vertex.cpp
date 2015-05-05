#include "game/block_vertex.h"

#include "general/vector_3f.h"

namespace block_game
{
  BlockVertex::BlockVertex()
  {}

  BlockVertex::BlockVertex(const Vector3F& position, const Vector3F& normal, const Vector3F& color)
    : position{position}, normal{normal}, color{color}
  {}
}
