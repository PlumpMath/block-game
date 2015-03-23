#ifndef BLOCK_GAME_BLOCK_H_
#define BLOCK_GAME_BLOCK_H_

#include "vector_3d.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float radius, const Vector3D& position, const Vector3D& direction);

    float radius() const;
    Vector3D& position();
    Vector3D& rotation();

    void Draw() const;

  private:
    const float radius_;
    Vector3D position_;
    Vector3D rotation_;
  };
}

#endif
