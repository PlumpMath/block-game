#ifndef BLOCK_GAME_GENERAL_VECTOR_3D_H_
#define BLOCK_GAME_GENERAL_VECTOR_3D_H_

namespace block_game
{
  struct Vector3D
  {
  public:
    static const int kDimensions = 3;

    Vector3D();
    Vector3D(const float, const float, const float);

    float operator[](int) const;
    float& operator[](int);

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
