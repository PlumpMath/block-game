#include "general/vector_3f.h"

#include <cmath>

namespace block_game
{
  Vector3F::Vector3F() : x{0.0F}, y{0.0F}, z{0.0F}
  {}

  Vector3F::Vector3F(const float x, const float y, const float z) : x{x}, y{y}, z{z}
  {}

  float Vector3F::operator[](const int i) const
  {
    return components[i];
  }

  float& Vector3F::operator[](const int i)
  {
    return components[i];
  }

  Vector3F Vector3F::operator+(const Vector3F& vector_3f) const
  {
    return Vector3F{x + vector_3f.x, y + vector_3f.y, z + vector_3f.z};
  }

  Vector3F Vector3F::operator-(const Vector3F& vector_3f) const
  {
    return Vector3F{x - vector_3f.x, y - vector_3f.y, z - vector_3f.z};
  }

  Vector3F Vector3F::operator*(const float scalar) const
  {
    return Vector3F{x * scalar, y * scalar, z * scalar};
  }

  Vector3F Vector3F::operator/(const float scalar) const
  {
    return Vector3F{x / scalar, y / scalar, z / scalar};
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

  void Vector3F::RotateX(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_y{y * cosine - z * sine};
    const float new_z{y * sine + z * cosine};

    y = new_y;
    z = new_z;
  }

  void Vector3F::RotateY(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_x{z * sine + x * cosine};
    const float new_z{z * cosine - x * sine};

    x = new_x;
    z = new_z;
  }

  void Vector3F::RotateZ(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_x{x * cosine - y * sine};
    const float new_y{x * sine + y * cosine};

    x = new_x;
    y = new_y;
  }

  Vector3F operator*(const float scalar, const Vector3F& vector_3f)
  {
    return Vector3F{scalar * vector_3f.x, scalar * vector_3f.y, scalar * vector_3f.z};
  }

  Vector3F operator/(const float scalar, const Vector3F& vector_3f)
  {
    return Vector3F{scalar / vector_3f.x, scalar / vector_3f.y, scalar / vector_3f.z};
  }
}
