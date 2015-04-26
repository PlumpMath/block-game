#ifndef BLOCK_GAME_GAME_BLOCK_VERTEX_H_
#define BLOCK_GAME_GAME_BLOCK_VERTEX_H_

#include "general/color_3f.h"
#include "general/vector_3f.h"

namespace block_game
{
  struct BlockVertex
  {
    BlockVertex();
    BlockVertex(const Vector3F&, const Vector3F&, const Color3F&);

    Vector3F position;
    Vector3F normal;
    Color3F color;
  };
}

#endif
