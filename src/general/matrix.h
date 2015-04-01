#ifndef BLOCK_GAME_GENERAL_MATRIX_H_
#define BLOCK_GAME_GENERAL_MATRIX_H_

namespace block_game
{
  template <int order>
  class Matrix
  {
  public:
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

  private:
    float elements[order][order];
  };
}

#endif
