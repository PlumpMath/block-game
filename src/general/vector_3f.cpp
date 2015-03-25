#include "general/vector_3f.h"

namespace block_game
{
  Vector3F::Vector3F() : x(0.0F), y(0.0F), z(0.0F)
  {}

  Vector3F::Vector3F(const float x, const float y, const float z) : x(x), y(y), z(z)
  {}

  float Vector3F::operator[](int i) const
  {
    return components[i];
  }

  float& Vector3F::operator[](int i)
  {
    return components[i];
  }
}
