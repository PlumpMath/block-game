#include "game/grid.h"

#include "general/color_3f.h"
#include "general/matrix.h"
#include "general/vector_3f.h"
#include "opengl/index_buffer.h"
#include "opengl/program.h"
#include "opengl/vertex_buffer.h"

namespace block_game
{
  const Vector3F vertices_[][2]
  {
    // -x
    {{-1.0F, -1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, 1.0F, -1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, -1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}},
    {{-1.0F, 1.0F, 1.0F}, {-1.0F, 0.0F, 0.0F}},
    // +x
    {{1.0F, -1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, 1.0F, -1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, -1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},
    {{1.0F, 1.0F, 1.0F}, {1.0F, 0.0F, 0.0F}},
    // -y
    {{-1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, -1.0F, 0.0F}},
    {{-1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, -1.0F, 0.0F}},
    // +y
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 1.0F, 0.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 1.0F, 0.0F}},
    // -z
    {{-1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{1.0F, -1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{-1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    {{1.0F, 1.0F, -1.0F}, {0.0F, 0.0F, -1.0F}},
    // +z
    {{-1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{1.0F, -1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{-1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}},
    {{1.0F, 1.0F, 1.0F}, {0.0F, 0.0F, 1.0F}}
  };
  const unsigned char indices_[]
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

  Grid::Grid(const float radius, const Color3F& color)
    : radius_{radius}, block_{radius, color, Vector3F{1.0F, 1.0F, 1.0F}}
  {}

  float Grid::radius() const
  {
    return radius_;
  }

  const Vector3F& Grid::position() const
  {
    return position_;
  }

  const Vector3F& Grid::rotation() const
  {
    return rotation_;
  }

  Vector3F& Grid::position()
  {
    return position_;
  }

  Vector3F& Grid::rotation()
  {
    return rotation_;
  }

  void Grid::Update(const double delta)
  {
    position_.RotateZ(static_cast<float>(delta));

    rotation_.x += static_cast<float>((1 - block_.color().r) * delta);
    rotation_.y += static_cast<float>((1 - block_.color().g) * delta);
    rotation_.z += static_cast<float>((1 - block_.color().b) * delta);
  }

  void Grid::Draw(Program& program) const
  {
    Matrix<3> rotation;
    rotation.RotateY(rotation_.y);
    rotation.RotateX(rotation_.x);
    rotation.RotateZ(rotation_.z);

    program.SetUniformFloat("radius", radius_);
    program.SetUniformVector3F("position", position_);
    program.SetUniformMatrix3("rotation", rotation);

    block_.Draw(program);
  }
}
