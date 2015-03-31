#ifndef BLOCK_GAME_GENERAL_MATRIX_3F_H_
#define BLOCK_GAME_GENERAL_MATRIX_3F_H_

namespace block_game
{
  struct Vector3F;

  struct Matrix3F
  {
    static const int kDimensions = 3;

    Matrix3F();

    const float* operator[](const int) const;
    float* operator[](const int);

    Matrix3F operator+(const Matrix3F&) const;
    Matrix3F operator-(const Matrix3F&) const;
    Matrix3F operator*(const Matrix3F&) const;

    Matrix3F& operator+=(const Matrix3F&);
    Matrix3F& operator-=(const Matrix3F&);

    void Scale(const float);
    void RotateX(const float);
    void RotateY(const float);
    void RotateZ(const float);

    float elements[kDimensions][kDimensions];
  };
}

#endif
