#include "general/color_3f.h"

namespace block_game
{
  Color3F::Color3F() : r(0.0F), g(0.0F), b(0.0F)
  {}

  Color3F::Color3F(const float r, const float g, const float b) : r(r), g(g), b(b)
  {}

  float Color3F::operator[](const int i) const
  {
    return components[i];
  }

  float& Color3F::operator[](const int i)
  {
    return components[i];
  }

  Color3F Color3F::operator+(const Color3F& color_3f) const
  {
    return {r + color_3f.r, g + color_3f.g, b + color_3f.b};
  }

  Color3F Color3F::operator-(const Color3F& color_3f) const
  {
    return {r - color_3f.r, g - color_3f.g, b - color_3f.b};
  }

  Color3F& Color3F::operator+=(const Color3F& color_3f)
  {
    r += color_3f.r;
    g += color_3f.g;
    b += color_3f.b;

    return *this;
  }

  Color3F& Color3F::operator-=(const Color3F& color_3f)
  {
    r -= color_3f.r;
    g -= color_3f.g;
    b -= color_3f.b;

    return *this;
  }

  Color3F& Color3F::operator*=(const float scalar)
  {
    r *= scalar;
    g *= scalar;
    b *= scalar;

    return *this;
  }

  Color3F& Color3F::operator/=(const float scalar)
  {
    r /= scalar;
    g /= scalar;
    b /= scalar;

    return *this;
  }
}
