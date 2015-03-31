#include "general/matrix_4f.h"

#include "general/vector_3f.h"

namespace block_game
{
  Matrix4F::Matrix4F()
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] = i == j ? 1.0F : 0.0F;
      }
    }
  }

  const float* Matrix4F::operator[](const int i) const
  {
    return elements[i];
  }

  float* Matrix4F::operator[](const int i)
  {
    return elements[i];
  }

  Matrix4F Matrix4F::operator+(const Matrix4F& matrix_4f) const
  {
    Matrix4F result;

    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        result[i][j] = elements[i][j] + matrix_4f[i][j];
      }
    }

    return result;
  }

  Matrix4F Matrix4F::operator-(const Matrix4F& matrix_4f) const
  {
    Matrix4F result;

    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        result[i][j] = elements[i][j] - matrix_4f[i][j];
      }
    }

    return result;
  }

  Matrix4F Matrix4F::operator*(const Matrix4F& matrix_4f) const
  {
    Matrix4F result;
    for (int i = 0; i < kDimensions; ++i)
    {
      result[i][i] = 0.0F;
    }

    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        for (int k = 0; k < kDimensions; ++k)
        {
          result[i][j] += elements[i][k] * matrix_4f[k][j];
        }
      }
    }

    return result;
  }

  Matrix4F& Matrix4F::operator+=(const Matrix4F& matrix_4f)
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] += matrix_4f[i][j];
      }
    }

    return *this;
  }

  Matrix4F& Matrix4F::operator-=(const Matrix4F& matrix_4f)
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] -= matrix_4f[i][j];
      }
    }

    return *this;
  }

  void Matrix4F::Translate(const Vector3F& vector_3f)
  {
    elements[0][3] += vector_3f.x;
    elements[1][3] += vector_3f.y;
    elements[2][3] += vector_3f.z;
  }
}
