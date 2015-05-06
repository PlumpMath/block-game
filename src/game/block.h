#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <memory>
#include <vector>

#include "game/block_vertex.h"
#include "general/vector.h"

namespace block_game
{
  class Program;

  class Block
  {
  public:
    Block(const Block*, const float, const Vector<3>&);
    ~Block();

    Block(Block&);
    Block(Block&&);

    const Block* parent() const;
    float radius() const;
    const Vector<3>& position() const;
    bool leaf() const;

    // leaf_ == false
    const Block* Child(const int, const int, const int) const;
    Block* Child(const int, const int, const int);

    // leaf_ == true
    bool solid() const;
    const Vector<3>& color() const;
    void set_solid(const bool);
    Vector<3>& color();

    void Merge();
    void Split();

    void BuildDraw(std::vector<const BlockVertex>&, std::vector<const unsigned char>&);
    void Draw(Program&) const;

  private:
    static const BlockVertex vertices_[];
    static const unsigned char indices_[];

    const Block* parent_;
    const float radius_;
    const Vector<3> position_;
    bool leaf_;

    // leaf_ == false
    std::unique_ptr<Block> children[2][2][2];

    // leaf_ == true
    bool solid_;
    Vector<3> color_;
  };
}

#endif
