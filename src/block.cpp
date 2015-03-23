#include "block.h"

namespace block_game
{
  Block::Block(const float side_length, const Vector3D& position, const Vector3D& direction)
    : side_length_(side_length), position_(position), direction_(direction)
  {
  }

  const float Block::side_length() const
  {
    return side_length_;
  }

  const Vector3D& Block::position() const
  {
    return position_;
  }

  const Vector3D& Block::direction() const
  {
    return direction_;
  }
}
