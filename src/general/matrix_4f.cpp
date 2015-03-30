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

  Matrix4F Matrix4F::operator+(const Vector3F& vector_3f) const
  {
    Matrix4F matrix_4f(*this);
    matrix_4f.elements[0][3] += vector_3f.x;
    matrix_4f.elements[1][3] += vector_3f.y;
    matrix_4f.elements[2][3] += vector_3f.z;
    return matrix_4f;
  }

  Matrix4F Matrix4F::operator-(const Vector3F& vector_3f) const
  {
    Matrix4F matrix_4f(*this);
    matrix_4f.elements[0][3] -= vector_3f.x;
    matrix_4f.elements[1][3] -= vector_3f.y;
    matrix_4f.elements[2][3] -= vector_3f.z;
    return matrix_4f;
  }
}
