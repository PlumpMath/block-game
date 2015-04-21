#ifndef BLOCK_GAME_GENERAL_CAMERA_H_
#define BLOCK_GAME_GENERAL_CAMERA_H_

#include "general/vector_3f.h"

namespace block_game
{
  class Camera
  {
  public:
    Camera();

    const Vector3F& position() const;
    const Vector3F& rotation() const;

    float field_of_view() const;
    float z_near() const;
    float z_far() const;
    float aspect_ratio() const;

  private:
    Vector3F position_;
    Vector3F rotation_;

    float field_of_view_;
    float z_near_;
    float z_far_;
    float aspect_ratio_;
  };
}

#endif
