#include "game/grid.h"

#include <cassert>
#include <vector>

#include <glad/glad.h>
#include <json/json.h>

#include "game/block_vertex.h"
#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/buffer.h"
#include "opengl/program.h"
#include "opengl/vertex_attribute.h"

namespace block_game
{
Grid::Grid(const float radius)
  : root_{*this, radius},
  vertex_buffer_{GL_ARRAY_BUFFER, 0, GL_STATIC_DRAW}, index_buffer_{GL_ELEMENT_ARRAY_BUFFER, 0, GL_STATIC_DRAW}
{
  assert(radius > 0.0F);
}

Grid::Grid(const Json::Value& value) : Grid{value["radius"].asFloat()}
{
  if (value.isMember("position"))
  {
    position_ = value["position"];
  }

  if (value.isMember("rotation"))
  {
    rotation_ = value["rotation"];
  }

  root_.Build(value["root"]);
}

Vector<3> Grid::GetPosition() const
{
  return position_;
}

Vector<3> Grid::GetRotation() const
{
  return rotation_;
}

void Grid::SetPosition(const Vector<3>& position)
{
  position_ = position;
}

void Grid::SetRotation(const Vector<3>& rotation)
{
  rotation_ = rotation;
}

const Block& Grid::GetRoot() const
{
  return root_;
}

Block& Grid::GetRoot()
{
  return root_;
}

void Grid::Update(const double delta)
{
  assert(delta >= 0.0);
}

void Grid::RebuildDraw()
{
  std::vector<BlockVertex> vertices;
  std::vector<unsigned char> indices;
  root_.BuildDraw(vertices, indices);

  vertex_buffer_.Resize(sizeof(BlockVertex) * vertices.size());
  if (vertices.size() > 0)
  {
    vertex_buffer_.SetData(&vertices[0]);
  }

  index_buffer_.Resize(indices.size());
  if (indices.size() > 0)
  {
    index_buffer_.SetData(&indices[0]);
  }
}

void Grid::Draw(Program& program)
{
  Matrix<3> rotation;
  rotation.RotateY(rotation_[1]);
  rotation.RotateX(rotation_[0]);
  rotation.RotateZ(rotation_[2]);

  program.SetUniformVector3("position", position_);
  program.SetUniformMatrix3("rotation", rotation);

  std::vector<VertexAttribute> attributes;
  attributes.emplace_back("in_Vertex", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), 0);
  attributes.emplace_back("in_Normal", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), sizeof(Vector<3>));
  attributes.emplace_back("in_Color", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), 2 * sizeof(Vector<3>));

  program.Draw(vertex_buffer_, index_buffer_, attributes);
}
}
