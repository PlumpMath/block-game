#ifndef BLOCK_GAME_BLOCK_H_
#define BLOCK_GAME_BLOCK_H_

#include "vector_3d.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float radius, const Vector3D& position, const Vector3D& direction);

    const float radius() const;
    const Vector3D& position() const;
    const Vector3D& rotation() const;

    void Draw() const;

  private:
    const float radius_;
    const Vector3D position_;
    const Vector3D rotation_;
  };
}

#endif
