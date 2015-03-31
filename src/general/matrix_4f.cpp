#include "general/matrix_4f.h"

#include "general/vector_3f.h"

namespace block_game
{
  Matrix4F::Matrix4F()
  {
    elements[0][0] = 1.0F;
    elements[0][1] = 0.0F;
    elements[0][2] = 0.0F;
    elements[0][3] = 0.0F;

    elements[1][0] = 0.0F;
    elements[1][1] = 1.0F;
    elements[1][2] = 0.0F;
    elements[1][3] = 0.0F;

    elements[2][0] = 0.0F;
    elements[2][1] = 0.0F;
    elements[2][2] = 1.0F;
    elements[2][3] = 0.0F;

    elements[3][0] = 0.0F;
    elements[3][1] = 0.0F;
    elements[3][2] = 0.0F;
    elements[3][3] = 1.0F;
  }

  const float* Matrix4F::operator[](const int i) const
  {
    return elements[i];
  }

  float* Matrix4F::operator[](const int i)
  {
    return elements[i];
  }

  void Matrix4F::Translate(const Vector3F& vector_3f)
  {
    elements[0][3] += vector_3f.x;
    elements[1][3] += vector_3f.y;
    elements[2][3] += vector_3f.z;
  }
}
