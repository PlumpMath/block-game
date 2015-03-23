#ifndef BLOCK_GAME_VECTOR_3D_H_
#define BLOCK_GAME_VECTOR_3D_H_

namespace block_game
{
  const int kDimensions = 3;

  struct Vector3D
  {
  public:
    Vector3D();

    float operator[](int i) const;
    float& operator[](int i);

    union
    {
      float components[kDimensions];
      struct
      {
        float x;
        float y;
        float z;
      };
    };
  };
}

#endif
