#include "block.h"

namespace block_game
{
  Block::Block(const float side_length, const Vector3D& position, const Vector3D& rotation)
    : side_length_(side_length), position_(position), rotation_(rotation)
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

  const Vector3D& Block::rotation() const
  {
    return rotation_;
  }

  void Block::Draw() const
  {

  }
}
