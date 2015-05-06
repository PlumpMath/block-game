#include "game/grid.h"

#include <cassert>
#include <vector>

#include <glad/glad.h>

#include "game/block_vertex.h"
#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/buffer.h"
#include "opengl/program.h"

namespace block_game
{
  Grid::Grid(const float radius) : root_{nullptr, radius, {0.0F, 0.0F, 0.0F}},
    vertex_buffer_{GL_ARRAY_BUFFER, 0, GL_STATIC_DRAW}, index_buffer_{GL_ELEMENT_ARRAY_BUFFER, 0, GL_STATIC_DRAW}
  {
    assert(radius > 0.0F);
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
    if (delta > 0.0)
    {
      position_.RotateZ(static_cast<float>(delta));

      const Block* color_block{&root_};
      while (!color_block->IsLeaf())
      {
        color_block = &color_block->GetChild(0, 0, 0);
      }
      rotation_ += (Vector<3>{1.0F, 1.0F, 1.0f} - color_block->GetColor()) * static_cast<float>(delta);
    }
  }

  void Grid::RebuildDraw()
  {
    std::vector<const BlockVertex> vertices;
    std::vector<const unsigned char> indices;
    root_.BuildDraw(vertices, indices);

    vertex_buffer_.Resize(sizeof(BlockVertex) * vertices.size());
    vertex_buffer_.SetData(&vertices[0]);

    index_buffer_.Resize(indices.size());
    index_buffer_.SetData(&indices[0]);
  }

  void Grid::Draw(Program& program)
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_[1]);
    rotation.RotateX(rotation_[0]);
    rotation.RotateZ(rotation_[2]);

    program.SetUniformVector3("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    std::vector<const VertexAttribute> attributes;

    attributes.emplace_back(program.GetAttribLocation("in_Vertex"), 3, GL_FLOAT,
      GL_FALSE, sizeof(BlockVertex), 0);

    attributes.emplace_back(program.GetAttribLocation("in_Normal"), 3, GL_FLOAT,
      GL_FALSE, sizeof(BlockVertex), sizeof(Vector<3>));

    attributes.emplace_back(program.GetAttribLocation("in_Color"), 3, GL_FLOAT,
      GL_FALSE, sizeof(BlockVertex), 2 * sizeof(Vector<3>));

    Buffer::Draw(vertex_buffer_, index_buffer_, attributes);
  }
}
