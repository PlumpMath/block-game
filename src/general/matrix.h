#ifndef BLOCK_GAME_GENERAL_MATRIX_H_
#define BLOCK_GAME_GENERAL_MATRIX_H_

#include <cmath>

namespace block_game
{
  template<int order>
  struct Matrix
  {
    Matrix();

    const float* operator[](const int i) const;
    float* operator[](const int i);

    Matrix<order> operator+(const Matrix<order>& matrix) const;
    Matrix<order> operator-(const Matrix<order>& matrix) const;

    Matrix<order> operator*(const Matrix<order>& matrix) const;

    Matrix<order>& operator+=(const Matrix<order>& matrix);
    Matrix<order>& operator-=(const Matrix<order>& matrix);

    void RotateX(const float angle); // Rotate around the x-axis
    void RotateY(const float angle); // Rotate around the y-axis
    void RotateZ(const float angle); // Rotate around the z-axis

    float elements[order][order];
  };

  template<int order>
  Matrix<order>::Matrix()
  {
    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        elements[i][j] = i == j ? 1.0F : 0.0F;
      }
    }
  }

  template<int order>
  const float* Matrix<order>::operator[](const int i) const
  {
    return elements[i];
  }

  template<int order>
  float* Matrix<order>::operator[](const int i)
  {
    return elements[i];
  }

  template<int order>
  Matrix<order> Matrix<order>::operator+(const Matrix<order>& matrix) const
  {
    Matrix<order> result;

    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        result[i][j] = elements[i][j] + matrix[i][j];
      }
    }

    return result;
  }

  template<int order>
  Matrix<order> Matrix<order>::operator-(const Matrix<order>& matrix) const
  {
    Matrix<order> result;

    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        result[i][j] = elements[i][j] - matrix[i][j];
      }
    }

    return result;
  }

  template<int order>
  Matrix<order> Matrix<order>::operator*(const Matrix<order>& matrix) const
  {
    Matrix<order> result;
    for (int i = 0; i < order; ++i)
    {
      result[i][i] = 0.0F;
    }

    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        for (int k = 0; k < order; ++k)
        {
          result[i][j] += elements[i][k] * matrix[k][j];
        }
      }
    }

    return result;
  }

  template<int order>
  Matrix<order>& Matrix<order>::operator+=(const Matrix<order>& matrix)
  {
    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        elements[i][j] += matrix[i][j];
      }
    }

    return *this;
  }

  template<int order>
  Matrix<order>& Matrix<order>::operator-=(const Matrix<order>& matrix)
  {
    for (int i = 0; i < order; ++i)
    {
      for (int j = 0; j < order; ++j)
      {
        elements[i][j] -= matrix[i][j];
      }
    }

    return *this;
  }

  template<int order>
  void Matrix<order>::RotateX(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    Matrix<order> rotation;
    rotation[1][1] = cosine;
    rotation[1][2] = -sine;
    rotation[2][1] = sine;
    rotation[2][2] = cosine;

    *this = rotation * *this;
  }

  template<int order>
  void Matrix<order>::RotateY(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    Matrix<order> rotation;
    rotation[0][0] = cosine;
    rotation[0][2] = sine;
    rotation[2][0] = -sine;
    rotation[2][2] = cosine;

    *this = rotation * *this;
  }

  template<int order>
  void Matrix<order>::RotateZ(const float angle)
  {
    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    Matrix<order> rotation;
    rotation[0][0] = cosine;
    rotation[0][1] = -sine;
    rotation[1][0] = sine;
    rotation[1][1] = cosine;

    *this = rotation * *this;
  }
}

#endif
