#ifndef BLOCK_GAME_GENERAL_MATRIX_4F_H_
#define BLOCK_GAME_GENERAL_MATRIX_4F_H_

namespace block_game
{
  struct Vector3F;

  struct Matrix4F
  {
    static const int kDimensions = 4;

    Matrix4F();

    const float* operator[](const int) const;
    float* operator[](const int);

    void Translate(const Vector3F&);

    float elements[kDimensions][kDimensions];
  };
}

#endif
