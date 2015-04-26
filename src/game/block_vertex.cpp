#include "game/block_vertex.h"

#include "general/color_3f.h"
#include "general/vector_3f.h"

namespace block_game
{
  BlockVertex::BlockVertex()
  {}

  BlockVertex::BlockVertex(const Vector3F& position, const Vector3F& normal, const Color3F& color)
    : position{position}, normal{normal}, color{color}
  {}
}
