#include "general/vector_2f.h"

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
}
