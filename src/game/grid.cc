#include "block_game/game/grid.h"

#include <cassert>
#include <vector>

#include <glad/glad.h>
#include <json/json.h>

#include "block_game/game/block_vertex.h"
#include "block_game/general/matrix.h"
#include "block_game/general/vector.h"
#include "block_game/opengl/buffer.h"
#include "block_game/opengl/program.h"
#include "block_game/opengl/vertex_attribute.h"

namespace block_game {
Grid::Grid(const float radius) :
  root_{*this, radius},

  vertex_buffer_{GL_ARRAY_BUFFER, 0, GL_STATIC_DRAW},
  index_buffer_{GL_ELEMENT_ARRAY_BUFFER, 0, GL_STATIC_DRAW}
{
  assert(0.0F < radius);
}

Grid::Grid(const Json::Value& value) : Grid{value["radius"].asFloat()} {
  if (value.isMember("position")) {
    position_ = value["position"];
  }
  if (value.isMember("rotation")) {
    rotation_ = value["rotation"];
  }
  root_.Build(value["root"]);
}

Vector<3> Grid::GetPosition() const {
  return position_;
}

Vector<3> Grid::GetRotation() const {
  return rotation_;
}

void Grid::SetPosition(const Vector<3>& position) {
  position_ = position;
}

void Grid::SetRotation(const Vector<3>& rotation) {
  rotation_ = rotation;
}

const Block& Grid::GetRoot() const {
  return root_;
}

Block& Grid::GetRoot() {
  return root_;
}

void Grid::Update(const double delta_seconds) {
  assert(0.0 <= delta_seconds);
}

void Grid::RebuildDraw() {
  std::vector<BlockVertex> vertices;
  std::vector<unsigned char> indices;
  root_.BuildDraw(vertices, indices);

  vertex_buffer_.Resize(sizeof(BlockVertex) * vertices.size());
  if (0 < vertices.size()) {
    vertex_buffer_.SetData(&vertices[0]);
  }

  index_buffer_.Resize(indices.size());
  if (0 < indices.size()) {
    index_buffer_.SetData(&indices[0]);
  }
}

void Grid::Draw(Program& program) {
  Matrix<3> rotation;
  rotation.RotateAboutY(rotation_[1]);
  rotation.RotateAboutX(rotation_[0]);
  rotation.RotateAboutZ(rotation_[2]);

  program.SetUniformVector3("u_Position", position_);
  program.SetUniformMatrix3("u_Rotation", rotation);

  std::vector<VertexAttribute> attributes;
  attributes.emplace_back("a_Vertex", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), 0);
  attributes.emplace_back("a_Normal", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), sizeof(Vector<3>));
  attributes.emplace_back("a_Color", 3, GL_FLOAT, GL_FALSE, sizeof(BlockVertex), 2 * sizeof(Vector<3>));

  program.Draw(vertex_buffer_, index_buffer_, attributes);
}
}
