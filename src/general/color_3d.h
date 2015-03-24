#ifndef BLOCK_GAME_GENERAL_COLOR_3D_H_
#define BLOCK_GAME_GENERAL_COLOR_3D_H_

namespace block_game
{
  struct Color3D
  {
  public:
    static const int kDimensions = 3;

    Color3D();
    Color3D(const float rComponent, const float gComponent, const float bComponent);

    float operator[](int i) const;
    float& operator[](int i);

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
