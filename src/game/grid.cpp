#include "game/grid.h"

#include <cassert>
#include <vector>

#include <glad/glad.h>

#include "game/block_vertex.h"
#include "general/matrix.h"
#include "general/vector.h"
#include "opengl/index_buffer.h"
#include "opengl/program.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  Grid::Grid(const float radius) : root_{nullptr, radius, {0.0F, 0.0F, 0.0F}}
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
    num_indices_ = indices.size();

    vertex_buffer_.Bind();
    vertex_buffer_.SetData(sizeof(BlockVertex) * vertices.size(), &vertices[0]);
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.SetData(indices.size(), &indices[0]);
    IndexBuffer::Unbind();
  }

  void Grid::Draw(Program& program)
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_[1]);
    rotation.RotateX(rotation_[0]);
    rotation.RotateZ(rotation_[2]);

    program.SetUniformVector3("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    vertex_buffer_.Bind();

    glVertexAttribPointer(program.GetAttribLocation("in_Vertex"), 3,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), 0);

    glVertexAttribPointer(program.GetAttribLocation("in_Normal"), 3,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), (void*) (1 * sizeof(Vector<3>)));

    glVertexAttribPointer(program.GetAttribLocation("in_Color"), 3,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), (void*) (2 * sizeof(Vector<3>)));

    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.Draw(num_indices_, GL_UNSIGNED_BYTE);
    IndexBuffer::Unbind();
  }
}
