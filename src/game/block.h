#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include "general/color_3f.h"
#include "general/vector_2f.h"
#include "general/vector_3f.h"

namespace block_game
{
  class Block
  {
  public:
    Block(const float, const Color3F&);

    float radius() const;
    const Color3F& color() const;
    Vector3F& position();
    Vector3F& rotation();

    void Update();
    void Draw() const;

  private:
    static const Vector2F points_[];

    const float radius_;
    const Color3F color_;
    Vector3F position_;
    Vector3F rotation_;
  };
}

#endif
