#include "color_3d.h"

namespace block_game
{
  Color3D::Color3D() : r(0.0F), g(0.0F), b(0.0F)
  {
  }

  Color3D::Color3D(const float rComponent, const float gComponent, const float bComponent)
    : r(rComponent), g(gComponent), b(bComponent)
  {
  }

  float Color3D::operator[](int i) const
  {
    return components[i];
  }

  float& Color3D::operator[](int i)
  {
    return components[i];
  }
}
