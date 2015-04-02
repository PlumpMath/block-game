#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include "general/color_3f.h"
#include "general/vector_3f.h"

namespace block_game
{
  class Program;

  class Block
  {
  public:
    Block(const float, const Color3F&);

    float radius() const;
    const Color3F& color() const;
    const Vector3F& position() const;
    const Vector3F& rotation() const;

    void Update(const double);
    void Draw(Program&) const;

  private:
    static const Vector3F vertices_[];
    static const Vector3F normals_[];
    static const int indices_[];

    const float radius_;
    const Color3F color_;
    Vector3F position_;
    Vector3F rotation_;
  };
}

#endif
