#include "game/block.h"

#include <memory>
#include <vector>

#include "game/block_vertex.h"
#include "general/vector.h"

namespace block_game
{
  const BlockVertex Block::vertices_[]
  {
    // -x
    {{-1.0F, -1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, 1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, -1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, 1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    // +x
    {{1.0F, -1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, -1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    // -y
    {{-1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    // +y
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}, {1.0F, 1.0F, 1.0F}},
    // -z
    {{-1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}, {1.0F, 1.0F, 1.0F}},
    // +z
    {{-1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}, {1.0F, 1.0F, 1.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}, {1.0F, 1.0F, 1.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}, {1.0F, 1.0F, 1.0F}}
  };
  const unsigned char Block::indices_[]
  {
    // -x
    0, 1, 3,
    0, 3, 2,
    // +x
    4, 6, 7,
    4, 7, 5,
    // -y
    8, 10, 11,
    8, 11, 9,
    // +y
    12, 13, 15,
    12, 15, 14,
    // -z
    16, 17, 19,
    16, 19, 18,
    // +z
    20, 22, 23,
    20, 23, 21
  };

  Block::Block(Block* const parent, const float radius, const Vector<3>& position)
    : parent_{parent}, radius_{radius}, position_(position), leaf_{true},
    solid_{false}
  {
    assert(radius > 0.0F);
  }

  Block::~Block()
  {}

  Block::Block(Block& block) : parent_{block.parent_}, radius_{block.radius_}, position_(block.position_), leaf_{block.leaf_}
  {
    if (leaf_)
    {
      solid_ = block.solid_;
      color_ = block.color_;
    }
    else
    {
      for (int z = 0; z < 2; ++z)
      {
        for (int y = 0; y < 2; ++y)
        {
          for (int x = 0; x < 2; ++x)
          {
            children[z][y][x] = std::move(block.children[z][y][x]);
          }
        }
      }
    }
  }

  Block::Block(Block&& block) : parent_{block.parent_}, radius_{block.radius_}, position_(block.position_), leaf_{block.leaf_}
  {
    if (leaf_)
    {
      solid_ = block.solid_;
      color_ = block.color_;
    }
    else
    {
      for (int z = 0; z < 2; ++z)
      {
        for (int y = 0; y < 2; ++y)
        {
          for (int x = 0; x < 2; ++x)
          {
            children[z][y][x] = std::move(block.children[z][y][x]);
          }
        }
      }
    }
  }

  bool Block::IsRoot() const
  {
    return parent_ == nullptr;
  }

  const Block& Block::GetParent() const
  {
    return *parent_;
  }

  Block& Block::GetParent()
  {
    return *parent_;
  }

  float Block::GetRadius() const
  {
    return radius_;
  }

  Vector<3> Block::GetPosition() const
  {
    return position_;
  }

  bool Block::IsLeaf() const
  {
    return leaf_;
  }

  const Block& Block::GetChild(const int x, const int y, const int z) const
  {
    assert(!leaf_ && x >= 0 && x < 2 && y >= 0 && y < 2 && z >= 0 && z < 2);
    return *children[z][y][x];
  }

  Block& Block::GetChild(const int x, const int y, const int z)
  {
    assert(!leaf_ && x >= 0 && x < 2 && y >= 0 && y < 2 && z >= 0 && z < 2);
    return *children[z][y][x];
  }

  bool Block::IsSolid() const
  {
    return solid_;
  }

  Vector<3> Block::GetColor() const
  {
    return color_;
  }

  void Block::SetSolid(const bool solid)
  {
    solid_ = solid;
  }

  void Block::SetColor(const Vector<3>& color)
  {
    color_ = color;
  }

  void Block::Merge()
  {
    leaf_ = true;

    for (int z = 0; z < 2; ++z)
    {
      for (int y = 0; y < 2; ++y)
      {
        for (int x = 0; x < 2; ++x)
        {
          children[z][y][x].reset();
        }
      }
    }
  }

  void Block::Split()
  {
    leaf_ = false;

    for (int z = 0; z < 2; ++z)
    {
      for (int y = 0; y < 2; ++y)
      {
        for (int x = 0; x < 2; ++x)
        {
          children[z][y][x] = std::make_unique<Block>(this, radius_ / 2,
            position_ + radius_ * Vector<3>{x - 0.5F, y - 0.5F, z - 0.5F});
          children[z][y][x]->SetSolid(solid_);
          children[z][y][x]->SetColor(color_);
        }
      }
    }
  }

  void Block::BuildDraw(std::vector<const BlockVertex>& vertices, std::vector<const unsigned char>& indices)
  {
    if (leaf_)
    {
      if (solid_)
      {
        for (int i = 0; i < 36; ++i)
        {
          indices.emplace_back(vertices.size() + indices_[i]);
        }

        for (int i = 0; i < 24; ++i)
        {
          vertices.emplace_back(position_ + radius_ * vertices_[i].position, vertices_[i].normal, color_);
        }
      }
    }
    else
    {
      for (auto& four : children)
      {
        for (auto& two : four)
        {
          for (auto& child : two)
          {
            child->BuildDraw(vertices, indices);
          }
        }
      }
    }
  }
}
