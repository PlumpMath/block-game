#ifndef BLOCK_GAME_BLOCK_H_
#define BLOCK_GAME_BLOCK_H_

#include "color_3d.h"
#include "vector_3d.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float radius, const Color3D& color);

    float radius() const;
    const Color3D& color() const;
    Vector3D& position();
    Vector3D& rotation();

    void Draw() const;

  private:
    const float radius_;
    const Color3D color_;
    Vector3D position_;
    Vector3D rotation_;
  };
}

#endif
