#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <vector>

#include "game/block_vertex.h"
#include "general/color_3f.h"
#include "general/vector_3f.h"

namespace block_game
{
  class Program;

  class Block
  {
  public:
    Block(const Block*, const float, const Vector3F&);

    const Block* parent() const;
    float radius() const;
    const Vector3F& position() const;
    bool leaf() const;

    const Block* Child(const int, const int, const int) const;
    Block* Child(const int, const int, const int);

    bool solid() const;
    const Color3F& color() const;
    void set_solid(const bool);
    Color3F& color();

    void Merge();
    void Split();

    void BuildDraw(std::vector<const BlockVertex>&, std::vector<const unsigned char>&);
    void Draw(Program&) const;

  private:
    static const BlockVertex vertices_[];
    static const unsigned char indices_[];

    const Block* parent_;
    const float radius_;
    const Vector3F position_;
    bool leaf_;

    Block* children[2][2][2];

    bool solid_;
    Color3F color_;
  };
}

#endif
