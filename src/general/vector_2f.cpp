#include "general/vector_2f.h"

#include <cmath>

namespace block_game
{
  Vector2F::Vector2F() : x(0.0F), y(0.0F)
  {}

  Vector2F::Vector2F(const float x, const float y) : x(x), y(y)
  {}

  float Vector2F::operator[](const int i) const
  {
    return components[i];
  }

  float& Vector2F::operator[](const int i)
  {
    return components[i];
  }

  void Vector2F::Rotate(const float angle)
  {
    // Caching sine and cosine yields 2x performance
    const float sine = sin(angle);
    const float cosine = cos(angle);
    const float new_x = x * cosine - y * sine;
    const float new_y = x * sine + y * cosine;
    x = new_x;
    y = new_y;
  }
}