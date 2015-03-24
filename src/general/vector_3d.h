#ifndef BLOCK_GAME_GENERAL_VECTOR_3D_H_
#define BLOCK_GAME_GENERAL_VECTOR_3D_H_

namespace block_game
{
  struct Vector3D
  {
  public:
    static const int kDimensions = 3;

    Vector3D();
    Vector3D(const float xComponent, const float yComponent, const float zComponent);

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
