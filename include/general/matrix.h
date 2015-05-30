#ifndef BLOCK_GAME_GENERAL_MATRIX_H_
#define BLOCK_GAME_GENERAL_MATRIX_H_

#include <cassert>
#include <cmath>

namespace block_game {
template<int order> class Matrix {
public:
  static_assert(order > 0, "Matrix with nonpositive order");

  Matrix();

  const float* operator[](size_t i) const;
  float* operator[](size_t i);

  Matrix<order> operator+(const Matrix<order>& matrix) const;
  Matrix<order> operator-(const Matrix<order>& matrix) const;

  Matrix<order> operator*(const Matrix<order>& matrix) const;

  Matrix<order>& operator+=(const Matrix<order>& matrix);
  Matrix<order>& operator-=(const Matrix<order>& matrix);

  void RotateX(float angle); // Rotate around the x-axis
  void RotateY(float angle); // Rotate around the y-axis
  void RotateZ(float angle); // Rotate around the z-axis

private:
  float elements[order][order];
};

template<int order> Matrix<order>::Matrix() {
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      elements[i][j] = i == j ? 1.0F : 0.0F;
    }
  }
}

template<int order> const float* Matrix<order>::operator[](const size_t i) const {
  assert(i < order);

  return elements[i];
}

template<int order> float* Matrix<order>::operator[](const size_t i) {
  assert(i < order);

  return elements[i];
}

template<int order> Matrix<order> Matrix<order>::operator+(const Matrix<order>& matrix) const {
  Matrix<order> result;
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      result[i][j] = elements[i][j] + matrix[i][j];
    }
  }
  return result;
}

template<int order> Matrix<order> Matrix<order>::operator-(const Matrix<order>& matrix) const {
  Matrix<order> result;
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      result[i][j] = elements[i][j] - matrix[i][j];
    }
  }
  return result;
}

template<int order> Matrix<order> Matrix<order>::operator*(const Matrix<order>& matrix) const {
  Matrix<order> result;
  for (size_t i = 0; i < order; ++i) {
    result[i][i] = 0.0F;
  }
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      for (size_t k = 0; k < order; ++k) {
        result[i][j] += elements[i][k] * matrix[k][j];
      }
    }
  }
  return result;
}

template<int order> Matrix<order>& Matrix<order>::operator+=(const Matrix<order>& matrix) {
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      elements[i][j] += matrix[i][j];
    }
  }
  return *this;
}

template<int order> Matrix<order>& Matrix<order>::operator-=(const Matrix<order>& matrix) {
  for (size_t i = 0; i < order; ++i) {
    for (size_t j = 0; j < order; ++j) {
      elements[i][j] -= matrix[i][j];
    }
  }
  return *this;
}

template<int order> void Matrix<order>::RotateX(const float angle) {
  static_assert(order >= 3, "rotate Matrix in x-axis without y-axis and z-axis");

  const float sine{sin(angle)};
  const float cosine{cos(angle)};

  Matrix<order> rotation;
  rotation[1][1] = cosine;
  rotation[1][2] = -sine;
  rotation[2][1] = sine;
  rotation[2][2] = cosine;

  *this = rotation * *this;
}

template<int order> void Matrix<order>::RotateY(const float angle) {
  static_assert(order >= 3, "rotate Matrix in y-axis without x-axis and z-axis");

  const float sine{sin(angle)};
  const float cosine{cos(angle)};

  Matrix<order> rotation;
  rotation[0][0] = cosine;
  rotation[0][2] = sine;
  rotation[2][0] = -sine;
  rotation[2][2] = cosine;

  *this = rotation * *this;
}

template<int order> void Matrix<order>::RotateZ(const float angle) {
  static_assert(order >= 2, "rotate Matrix in z-axis without x-axis and y-axis");

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
