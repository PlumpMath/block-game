#include "general/vector_3f.h"

namespace block_game
{
  Vector3F::Vector3F() : x(0.0F), y(0.0F), z(0.0F)
  {}

  Vector3F::Vector3F(const float x, const float y, const float z) : x(x), y(y), z(z)
  {}

  float Vector3F::operator[](const int i) const
  {
    return components[i];
  }

  float& Vector3F::operator[](const int i)
  {
    return components[i];
  }

  Vector3F& Vector3F::operator+=(const Vector3F& vector_3f)
  {
    x += vector_3f.x;
    y += vector_3f.y;
    z += vector_3f.z;

    return *this;
  }

  Vector3F& Vector3F::operator-=(const Vector3F& vector_3f)
  {
    x -= vector_3f.x;
    y -= vector_3f.y;
    z -= vector_3f.z;

    return *this;
  }

  Vector3F& Vector3F::operator*=(const float scalar)
  {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
  }

  Vector3F& Vector3F::operator/=(const float scalar)
  {
    x /= scalar;
    y /= scalar;
    z /= scalar;

    return *this;
  }
}
