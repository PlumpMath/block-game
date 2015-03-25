#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include "general/color_3d.h"
#include "general/vector_3d.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float, const Color3D&);

    float radius() const;
    const Color3D& color() const;
    Vector3D& position();
    Vector3D& rotation();

    void Update();
    void Draw() const;

  private:
    const float radius_;
    const Color3D color_;
    Vector3D position_;
    Vector3D rotation_;
  };
}

#endif
