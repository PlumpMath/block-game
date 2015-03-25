#ifndef BLOCK_GAME_GENERAL_COLOR_3F_H_
#define BLOCK_GAME_GENERAL_COLOR_3F_H_

namespace block_game
{
  struct Color3F
  {
  public:
    static const int kDimensions = 3;

    Color3F();
    Color3F(const float, const float, const float);

    float operator[](const int) const;
    float& operator[](const int);

    union
    {
      float components[kDimensions];
      struct
      {
        float r;
        float g;
        float b;
      };
    };
  };
}

#endif
