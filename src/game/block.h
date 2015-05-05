#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <vector>

#include "game/block_vertex.h"
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

    // leaf_ == false
    const Block* Child(const int, const int, const int) const;
    Block* Child(const int, const int, const int);

    // leaf_ == true
    bool solid() const;
    const Vector3F& color() const;
    void set_solid(const bool);
    Vector3F& color();

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

    // leaf_ == false
    Block* children[2][2][2];

    // leaf_ == true
    bool solid_;
    Vector3F color_;
  };
}

#endif
