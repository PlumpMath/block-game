#ifndef BLOCK_GAME_GENERAL_VECTOR_3F_H_
#define BLOCK_GAME_GENERAL_VECTOR_3F_H_

namespace block_game
{
  struct Vector3F
  {
  public:
    static const int kDimensions = 3;

    Vector3F();
    Vector3F(const float, const float, const float);

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
