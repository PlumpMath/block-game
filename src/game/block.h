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
    Block(Block* parent, float radius, const Vector<3>& position);

    bool IsRoot() const;
    const Block& GetParent() const;
    Block& GetParent();

    float GetRadius() const;
    Vector<3> GetPosition() const;
    bool IsLeaf() const;

    // leaf_ == false
    const Block& GetChild(int x, int y, int z) const;
    Block& GetChild(int x, int y, int z);

    // leaf_ == true
    bool IsSolid() const;
    Vector<3> GetColor() const;
    void SetSolid(bool solid);
    void SetColor(const Vector<3>& color);

    void Split();
    void Merge();

    void BuildDraw(std::vector<BlockVertex>& vertices, std::vector<unsigned char>& indices);

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
