#include "game/grid.h"

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

  void Grid::Draw(Program& program) const
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_.y);
    rotation.RotateX(rotation_.x);
    rotation.RotateZ(rotation_.z);

    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    root_.Draw(program);
  }
}
