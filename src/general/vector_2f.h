#ifndef BLOCK_GAME_GENERAL_VECTOR_2F_H_
#define BLOCK_GAME_GENERAL_VECTOR_2F_H_

namespace block_game
{
  struct Vector2F
  {
    static const int kDimensions = 2;

    Vector2F();
    Vector2F(const float, const float);

    float operator[](const int) const;
    float& operator[](const int);

    Vector2F operator+(const Vector2F&) const;
    Vector2F operator-(const Vector2F&) const;
    Vector2F operator*(const float) const;
    Vector2F operator/(const float) const;

    friend Vector2F operator*(const float, const Vector2F&);
    friend Vector2F operator/(const float, const Vector2F&);

    Vector2F& operator+=(const Vector2F&);
    Vector2F& operator-=(const Vector2F&);
    Vector2F& operator*=(const float);
    Vector2F& operator/=(const float);

    void Rotate(const float);

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
