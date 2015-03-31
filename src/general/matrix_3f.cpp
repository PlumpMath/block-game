#include "general/matrix_3f.h"

#include <cmath>

#include "general/vector_3f.h"

namespace block_game
{
  Matrix3F::Matrix3F()
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] = i == j ? 1.0F : 0.0F;
      }
    }
  }

  const float* Matrix3F::operator[](const int i) const
  {
    return elements[i];
  }

  float* Matrix3F::operator[](const int i)
  {
    return elements[i];
  }

  Matrix3F Matrix3F::operator+(const Matrix3F& matrix_3f) const
  {
    Matrix3F result;

    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        result[i][j] = elements[i][j] + matrix_3f[i][j];
      }
    }

    return result;
  }

  Matrix3F Matrix3F::operator-(const Matrix3F& matrix_3f) const
  {
    Matrix3F result;

    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        result[i][j] = elements[i][j] - matrix_3f[i][j];
      }
    }

    return result;
  }

  Matrix3F Matrix3F::operator*(const Matrix3F& matrix_3f) const
  {
    Matrix3F result;
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
          result[i][j] += elements[i][k] * matrix_3f[k][j];
        }
      }
    }

    return result;
  }

  Matrix3F& Matrix3F::operator+=(const Matrix3F& matrix_3f)
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] += matrix_3f[i][j];
      }
    }

    return *this;
  }

  Matrix3F& Matrix3F::operator-=(const Matrix3F& matrix_3f)
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      for (int j = 0; j < kDimensions; ++j)
      {
        elements[i][j] -= matrix_3f[i][j];
      }
    }

    return *this;
  }

  void Matrix3F::Scale(const float scale)
  {
    for (int i = 0; i < kDimensions; ++i)
    {
      elements[0][i] *= scale;
      elements[1][i] *= scale;
      elements[2][i] *= scale;
    }
  }

  void Matrix3F::RotateX(const float angle)
  {
    const float sine = sin(angle);
    const float cosine = cos(angle);

    Matrix3F rotation;
    rotation[1][1] = cosine;
    rotation[1][2] = -sine;
    rotation[2][1] = sine;
    rotation[2][2] = cosine;

    *this = rotation * *this;
  }

  void Matrix3F::RotateY(const float angle)
  {
    const float sine = sin(angle);
    const float cosine = cos(angle);

    Matrix3F rotation;
    rotation[0][0] = cosine;
    rotation[0][2] = sine;
    rotation[2][0] = -sine;
    rotation[2][2] = cosine;

    *this = rotation * *this;
  }

  void Matrix3F::RotateZ(const float angle)
  {
    const float sine = sin(angle);
    const float cosine = cos(angle);

    Matrix3F rotation;
    rotation[0][0] = cosine;
    rotation[0][1] = -sine;
    rotation[1][0] = sine;
    rotation[1][1] = cosine;

    *this = rotation * *this;
  }
}
