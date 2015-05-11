#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <vector>

#include "game/block_vertex.h"
#include "general/vector.h"

namespace block_game
{
  class Grid;

  class Block
  {
  public:
    Block(Grid& grid, float radius);
    Block(Block& parent, size_t x, size_t y, size_t z);

    float GetRadius() const;
    Vector<3> GetPosition() const;
    bool IsRoot() const;
    bool IsLeaf() const;

    // root_ == true
    const Grid& GetGrid() const;
    Grid& GetGrid();

    // root_ == false
    const Block& GetParent() const;
    Block& GetParent();

    // leaf_ == true
    bool IsSolid() const;
    Vector<3> GetColor() const;
    void SetSolid(bool solid);
    void SetColor(const Vector<3>& color);
    void Split();

    // leaf_ == false
    const Block& GetChild(size_t x, size_t y, size_t z) const;
    Block& GetChild(size_t x, size_t y, size_t z);
    void Merge();

    void BuildDraw(std::vector<BlockVertex>& vertices, std::vector<unsigned char>& indices);

  private:
    float radius_;
    Vector<3> position_;
    bool root_;
    bool leaf_;

    // root_ == true
    Grid* grid_;

    // root_ == false
    Block* parent_;

    // leaf_ == true
    bool solid_;
    Vector<3> color_;

    // leaf_ == false
    std::vector<Block> children_;
  };
}

#endif
