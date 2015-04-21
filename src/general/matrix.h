#ifndef BLOCK_GAME_GENERAL_MATRIX_H_
#define BLOCK_GAME_GENERAL_MATRIX_H_

#include <cmath>

namespace block_game
{
  template<int order> struct Matrix
  {
    Matrix()
    {
      for (int i = 0; i < order; ++i)
      {
        for (int j = 0; j < order; ++j)
        {
          elements[i][j] = i == j ? 1.0F : 0.0F;
        }
      }
    }

    const float* operator[](const int i) const
    {
      return elements[i];
    }

    float* operator[](const int i)
    {
      return elements[i];
    }

    Matrix<order> operator+(const Matrix<order>& matrix) const
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

    Matrix<order> operator-(const Matrix<order>& matrix) const
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

    Matrix<order> operator*(const Matrix<order>& matrix) const
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

    Matrix<order>& operator+=(const Matrix<order>& matrix)
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

    Matrix<order>& operator-=(const Matrix<order>& matrix)
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

    void RotateX(const float angle)
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

    void RotateY(const float angle)
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

    void RotateZ(const float angle)
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

    float elements[order][order];
  };
}

#endif
