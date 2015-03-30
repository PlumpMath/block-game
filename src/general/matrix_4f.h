#ifndef BLOCK_GAME_GENERAL_MATRIX_4F_H_
#define BLOCK_GAME_GENERAL_MATRIX_4F_H_

namespace block_game
{
  struct Vector3F;

  struct Matrix4F
  {
    static const int kDimensions = 4;

    Matrix4F();

    Matrix4F operator+(const Vector3F&) const;
    Matrix4F operator-(const Vector3F&) const;

    float elements[kDimensions][kDimensions];
  };
}

#endif
