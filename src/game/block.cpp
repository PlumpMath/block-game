#include "game/block.h"

#include <cassert>
#include <stdexcept>
#include <vector>

#include <json/json.h>

#include "game/block_vertex.h"
#include "game/grid.h"
#include "general/vector.h"

namespace {
const block_game::Vector<3> points[]{
  {-1.0F, -1.0F, -1.0f},
  {1.0F, -1.0F, -1.0f},
  {-1.0F, 1.0F, -1.0f},
  {1.0F, 1.0F, -1.0f},
  {-1.0F, -1.0F, 1.0f},
  {1.0F, -1.0F, 1.0f},
  {-1.0F, 1.0F, 1.0f},
  {1.0F, 1.0F, 1.0f}
};
const block_game::Vector<3> face_normals[]{
  {-1.0F, 0.0F, 0.0F},
  {1.0F, 0.0F, 0.0F},
  {0.0F, -1.0F, 0.0F},
  {0.0F, 1.0F, 0.0F},
  {0.0F, 0.0F, -1.0F},
  {0.0F, 0.0F, 1.0F},
};
const block_game::Vector<3> identity_color{1.0F, 1.0F, 1.0F};
const block_game::BlockVertex block_vertices[]{
  {points[0], face_normals[0], identity_color},
  {points[2], face_normals[0], identity_color},
  {points[4], face_normals[0], identity_color},
  {points[6], face_normals[0], identity_color},

  {points[1], face_normals[1], identity_color},
  {points[3], face_normals[1], identity_color},
  {points[5], face_normals[1], identity_color},
  {points[7], face_normals[1], identity_color},

  {points[0], face_normals[2], identity_color},
  {points[1], face_normals[2], identity_color},
  {points[4], face_normals[2], identity_color},
  {points[5], face_normals[2], identity_color},

  {points[2], face_normals[3], identity_color},
  {points[3], face_normals[3], identity_color},
  {points[6], face_normals[3], identity_color},
  {points[7], face_normals[3], identity_color},

  {points[0], face_normals[4], identity_color},
  {points[1], face_normals[4], identity_color},
  {points[2], face_normals[4], identity_color},
  {points[3], face_normals[4], identity_color},

  {points[4], face_normals[5], identity_color},
  {points[5], face_normals[5], identity_color},
  {points[6], face_normals[5], identity_color},
  {points[7], face_normals[5], identity_color}
};
const unsigned char block_indices[]{
  0, 1, 3,
  0, 3, 2,

  4, 6, 7,
  4, 7, 5,

  8, 10, 11,
  8, 11, 9,

  12, 13, 15,
  12, 15, 14,

  16, 17, 19,
  16, 19, 18,

  20, 22, 23,
  20, 23, 21
};
}

namespace block_game {
Block::Block(Grid& grid, const float radius) :
  radius_{radius},
  root_{true},
  leaf_{true},

  grid_{&grid},

  solid_{false}
{
  assert(radius > 0.0F);
}

Block::Block(Block& parent, const size_t x, const size_t y, const size_t z) :
  radius_{parent.radius_ / 2.0F},
  position_(parent.position_ + parent.radius_ * Vector<3>{x - 0.5F, y - 0.5F, z - 0.5F}),
  root_{false},
  leaf_{true},

  parent_{&parent},

  solid_{parent.solid_},
  color_(parent.color_)
{
  assert(x < 2);
  assert(y < 2);
  assert(z < 2);
}

void Block::Build(const Json::Value& value) {
  solid_ = value.get("solid", solid_).asBool();

  if (value.isMember("color")) {
    SetColor(value["color"]);
  }

  if (value.isMember("children")) {
    Split();
    const Json::Value& children{value["children"]};

    if (children.size() != children_.size()) {
      throw std::runtime_error{"incorrect number of Block children"};
    }

    for (size_t i{0}; i < children.size(); ++i) {
      children_[i].Build(children[i]);
    }
  }
}

float Block::GetRadius() const {
  return radius_;
}

Vector<3> Block::GetPosition() const {
  return position_;
}

bool Block::IsRoot() const {
  return root_;
}

bool Block::IsLeaf() const {
  return leaf_;
}

const Grid& Block::GetGrid() const {
  assert(root_);

  return *grid_;
}

Grid& Block::GetGrid() {
  assert(root_);

  return *grid_;
}

const Block& Block::GetParent() const {
  assert(!root_);

  return *parent_;
}

Block& Block::GetParent() {
  assert(!root_);

  return *parent_;
}

bool Block::IsSolid() const {
  assert(leaf_);

  return solid_;
}

Vector<3> Block::GetColor() const {
  assert(leaf_);

  return color_;
}

void Block::SetSolid(const bool solid) {
  assert(leaf_);

  solid_ = solid;
}

void Block::SetColor(const Vector<3>& color) {
  assert(leaf_);
  assert(color.IsInColorRange());

  color_ = color;
}

void Block::Split() {
  assert(leaf_);

  leaf_ = false;

  for (size_t z{0}; z < 2; ++z) {
    for (size_t y{0}; y < 2; ++y) {
      for (size_t x{0}; x < 2; ++x) {
        children_.emplace_back(*this, x, y, z);
        GetChild(x, y, z).SetSolid(solid_);
        GetChild(x, y, z).SetColor(color_);
      }
    }
  }
}

const Block& Block::GetChild(const size_t x, const size_t y, const size_t z) const {
  assert(!leaf_);
  assert(x < 2);
  assert(y < 2);
  assert(z < 2);

  return children_[z << 2 | y << 1 | x];
}

Block& Block::GetChild(const size_t x, const size_t y, const size_t z) {
  assert(!leaf_);
  assert(x < 2);
  assert(y < 2);
  assert(z < 2);

  return children_[z << 2 | y << 1 | x];
}

void Block::Merge() {
  assert(!leaf_);

  leaf_ = true;
  children_.clear();
}

void Block::BuildDraw(std::vector<BlockVertex>& vertices, std::vector<unsigned char>& indices) {
  if (leaf_) {
    if (solid_) {
      for (size_t i{0}; i < 36; ++i) {
        indices.emplace_back(static_cast<unsigned char>(vertices.size() + block_indices[i]));
      }

      for (size_t i{0}; i < 24; ++i) {
        vertices.emplace_back(position_ + radius_ * block_vertices[i].position, block_vertices[i].normal, color_);
      }
    }
  } else {
    for (auto& child : children_) {
      child.BuildDraw(vertices, indices);
    }
  }
}
}
