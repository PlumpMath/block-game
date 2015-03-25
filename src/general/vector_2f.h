#ifndef BLOCK_GAME_GENERAL_VECTOR_2F_H_
#define BLOCK_GAME_GENERAL_VECTOR_2F_H_

namespace block_game
{
  struct Vector2F
  {
  public:
    static const int kDimensions = 2;

    Vector2F();
    Vector2F(const float, const float);

    float operator[](const int) const;
    float& operator[](const int);

    union
    {
      float components[kDimensions];
      struct
      {
        float x;
        float y;
      };
    };
  };
}

#endif
