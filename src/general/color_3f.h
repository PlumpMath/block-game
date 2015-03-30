#ifndef BLOCK_GAME_GENERAL_COLOR_3F_H_
#define BLOCK_GAME_GENERAL_COLOR_3F_H_

namespace block_game
{
  struct Color3F
  {
    static const int kDimensions = 3;

    Color3F();
    Color3F(const float, const float, const float);

    float operator[](const int) const;
    float& operator[](const int);

    Color3F operator+(const Color3F&) const;
    Color3F operator-(const Color3F&) const;
    Color3F operator*(const float) const;
    Color3F operator/(const float) const;

    Color3F& operator+=(const Color3F&);
    Color3F& operator-=(const Color3F&);
    Color3F& operator*=(const float);
    Color3F& operator/=(const float);

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

  Color3F operator*(const float, const Color3F&);
  Color3F operator/(const float, const Color3F&);
}

#endif
