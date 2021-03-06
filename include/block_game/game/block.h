#ifndef BLOCK_GAME_GAME_BLOCK_H_
#define BLOCK_GAME_GAME_BLOCK_H_

#include <vector>

#include <json/json.h>

#include "block_game/game/block_vertex.h"
#include "block_game/general/vector.h"

namespace block_game {
class Grid;

class Block {
public:
  Block(Grid& grid, float radius);
  Block(Block& parent, int x, int y, int z);

  void Build(const Json::Value& value);

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
  const Block& GetChild(int x, int y, int z) const;
  Block& GetChild(int x, int y, int z);
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
