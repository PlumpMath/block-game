#include "vector_3d.h"

namespace block_game
{
  Vector3D::Vector3D() : x(0), y(0), z(0)
  {
  }

  float Vector3D::operator[](int i) const
  {
    return components[i];
  }

  float& Vector3D::operator[](int i)
  {
    return components[i];
  }
}
