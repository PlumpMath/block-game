#ifndef BLOCK_GAME_GENERAL_MATRIX_4F_H_
#define BLOCK_GAME_GENERAL_MATRIX_4F_H_

namespace block_game
{
  struct Matrix4F
  {
    static const int kDimensions = 4;

    Matrix4F();

    float elements[kDimensions][kDimensions];
  };
}

#endif
