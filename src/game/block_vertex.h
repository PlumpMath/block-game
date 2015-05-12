#ifndef BLOCK_GAME_GAME_BLOCK_VERTEX_H_
#define BLOCK_GAME_GAME_BLOCK_VERTEX_H_

#include "general/vector.h"

namespace block_game
{
struct BlockVertex
{
  BlockVertex(const Vector<3>& position, const Vector<3>& normal, const Vector<3>& color);

  Vector<3> position;
  Vector<3> normal;
  Vector<3> color;
};
}

#endif
