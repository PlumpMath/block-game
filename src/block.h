#ifndef BLOCK_GAME_BLOCK_H_
#define BLOCK_GAME_BLOCK_H_

#include "vector_3d.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float side_length, const Vector3D& position, const Vector3D& direction);

    const float side_length() const;
    const Vector3D& position() const;
    const Vector3D& direction() const;

  private:
    const float side_length_;
    const Vector3D position_;
    const Vector3D direction_;
  };
}

#endif
