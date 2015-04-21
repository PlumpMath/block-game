#include "general/camera.h"

#include "general/vector_3f.h"

namespace block_game
{
  Camera::Camera() : field_of_view_{0.0F}, z_near_{0.0F}, z_far_{0.0F}, aspect_ratio_{0.0F}
  {}

  const Vector3F& Camera::position() const
  {
    return position_;
  }

  const Vector3F& Camera::rotation() const
  {
    return rotation_;
  }

  float Camera::field_of_view() const
  {
    return field_of_view_;
  }

  float Camera::z_near() const
  {
    return z_near_;
  }

  float Camera::z_far() const
  {
    return z_far_;
  }

  float Camera::aspect_ratio() const
  {
    return aspect_ratio_;
  }
}
