#ifndef BLOCK_GAME_VECTOR_3D_H_
#define BLOCK_GAME_VECTOR_3D_H_

namespace block_game
{
  const int kDimensions = 3;

  union Vector3D
  {
    float points[kDimensions];
    struct
    {
      float x;
      float y;
      float z;
    };
  };
}

#endif
