#ifndef BLOCK_GAME_GENERAL_CAMERA_H_
#define BLOCK_GAME_GENERAL_CAMERA_H_

#include "general/vector_3f.h"

namespace block_game
{
  class Camera
  {
  public:
    Camera();

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
