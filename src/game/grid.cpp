#include "game/grid.h"

#include <vector>

#include <glad/glad.h>

#include "game/block_vertex.h"
#include "general/color_3f.h"
#include "general/matrix.h"
#include "general/vector_3f.h"
#include "opengl/index_buffer.h"
#include "opengl/program.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  Grid::Grid(const float radius) : root_{nullptr, radius, {0.0F, 0.0F, 0.0F}}
  {}

  const Vector3F& Grid::position() const
  {
    return position_;
  }

  const Vector3F& Grid::rotation() const
  {
    return rotation_;
  }

  const Block& Grid::root() const
  {
    return root_;
  }

  Vector3F& Grid::position()
  {
    return position_;
  }

  Vector3F& Grid::rotation()
  {
    return rotation_;
  }

  Block& Grid::root()
  {
    return root_;
  }

  void Grid::Update(const double delta)
  {
    position_.RotateZ(static_cast<float>(delta));

    rotation_.x += static_cast<float>((1 - root_.color().r) * delta);
    rotation_.y += static_cast<float>((1 - root_.color().g) * delta);
    rotation_.z += static_cast<float>((1 - root_.color().b) * delta);
  }

  void Grid::RebuildDraw()
  {
    std::vector<const BlockVertex> vertices;
    std::vector<const unsigned char> indices;
    root_.BuildDraw(vertices, indices);
    num_indices_ = indices.size();

    vertex_buffer_.Bind();
    vertex_buffer_.SetData(sizeof(BlockVertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.SetData(indices.size(), &indices[0], GL_STATIC_DRAW);
    IndexBuffer::Unbind();
  }

  void Grid::Draw(Program& program) const
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_.y);
    rotation.RotateX(rotation_.x);
    rotation.RotateZ(rotation_.z);

    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    vertex_buffer_.Bind();

    glVertexAttribPointer(program.GetAttribLocation("in_Vertex"), Vector3F::kDimensions,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), 0);

    glVertexAttribPointer(program.GetAttribLocation("in_Normal"), Vector3F::kDimensions,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), (void*) (1 * sizeof(Vector3F)));

    glVertexAttribPointer(program.GetAttribLocation("in_Color"), Color3F::kDimensions,
      GL_FLOAT, GL_TRUE, sizeof(BlockVertex), (void*) (2 * sizeof(Vector3F)));

    VertexBuffer::Unbind();

    index_buffer_.Bind();
    index_buffer_.Draw(num_indices_, GL_UNSIGNED_BYTE);
    IndexBuffer::Unbind();
  }
}
