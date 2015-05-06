#include "game/block.h"

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

  Block::Block(const Block* parent, const float radius, const Vector<3>& position)
    : parent_{parent}, radius_{radius}, position_(position), leaf_{true},
    solid_{false}
  {
    assert(radius > 0.0F);

    for (int z = 0; z < 2; ++z)
    {
      for (int y = 0; y < 2; ++y)
      {
        for (int x = 0; x < 2; ++x)
        {
          children[z][y][x] = nullptr;
        }
      }
    }
  }

  const Block* Block::parent() const
  {
    return parent_;
  }

  float Block::radius() const
  {
    return radius_;
  }

  const Vector<3>& Block::position() const
  {
    return position_;
  }

  bool Block::leaf() const
  {
    return leaf_;
  }

  const Block* Block::Child(const int x, const int y, const int z) const
  {
    assert(x >= 0 && x < 2 && y >= 0 && y < 2 && z >= 0 && z < 2);
    return children[z][y][x];
  }

  Block* Block::Child(const int x, const int y, const int z)
  {
    assert(x >= 0 && x < 2 && y >= 0 && y < 2 && z >= 0 && z < 2);
    return children[z][y][x];
  }

  bool Block::solid() const
  {
    return solid_;
  }

  const Vector<3>& Block::color() const
  {
    return color_;
  }

  void Block::set_solid(const bool is_solid)
  {
    solid_ = is_solid;
  }

  Vector<3>& Block::color()
  {
    return color_;
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
          delete children[z][y][x];
          children[z][y][x] = nullptr;
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
          children[z][y][x] = new Block{this, radius_ / 2, position_ + radius_ * Vector<3>{x - 0.5F, y - 0.5F, z - 0.5F}};
          children[z][y][x]->set_solid(solid_);
          Vector<3>& child_color = children[z][y][x]->color();
          child_color[0] = color_[0];
          child_color[1] = color_[1];
          child_color[2] = color_[2];
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
