#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <vector>

#include "game/block_vertex.h"
#include "general/vector.h"

namespace block_game
{
  class Block
  {
  public:
    Block(Block* const, const float, const Vector<3>&);

    bool IsRoot() const;
    const Block& GetParent() const;
    Block& GetParent();

    float GetRadius() const;
    Vector<3> GetPosition() const;
    bool IsLeaf() const;

    // leaf_ == false
    const Block& GetChild(const int, const int, const int) const;
    Block& GetChild(const int, const int, const int);

    // leaf_ == true
    bool IsSolid() const;
    Vector<3> GetColor() const;
    void SetSolid(const bool);
    void SetColor(const Vector<3>&);

    void Split();
    void Merge();

    void BuildDraw(std::vector<BlockVertex>&, std::vector<unsigned char>&);

  private:
    Block* parent_;
    float radius_;
    Vector<3> position_;
    bool leaf_;

    // leaf_ == false
    std::vector<Block> children_;

    // leaf_ == true
    bool solid_;
    Vector<3> color_;
  };
}

#endif
