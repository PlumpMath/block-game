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
    Block(Block* const, const float, const Vector<3>&);
    ~Block();

    Block(Block&);
    Block(Block&&);

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

    void Merge();
    void Split();

    void BuildDraw(std::vector<const BlockVertex>&, std::vector<const unsigned char>&);
    void Draw(Program&) const;

  private:
    static const BlockVertex vertices_[];
    static const unsigned char indices_[];

    Block* const parent_;
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
