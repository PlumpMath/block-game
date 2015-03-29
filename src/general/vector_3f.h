#ifndef BLOCK_GAME_GENERAL_VECTOR_3F_H_
#define BLOCK_GAME_GENERAL_VECTOR_3F_H_

namespace block_game
{
  struct Vector3F
  {
    static const int kDimensions = 3;

    Vector3F();
    Vector3F(const float, const float, const float);

    float operator[](const int) const;
    float& operator[](const int);

    Vector3F operator+(const Vector3F&) const;
    Vector3F operator-(const Vector3F&) const;
    Vector3F operator*(const float) const;
    Vector3F operator/(const float) const;

    friend Vector3F operator*(const float, const Vector3F&);
    friend Vector3F operator/(const float, const Vector3F&);

    Vector3F& operator+=(const Vector3F&);
    Vector3F& operator-=(const Vector3F&);
    Vector3F& operator*=(const float);
    Vector3F& operator/=(const float);

    void RotateX(const float); // Rotate around the x-axis
    void RotateY(const float); // Rotate around the y-axis
    void RotateZ(const float); // Rotate around the z-axis

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
