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

  Vector3F& Camera::position()
  {
    return position_;
  }

  Vector3F& Camera::rotation()
  {
    return rotation_;
  }

  void Camera::set_field_of_view(const float field_of_view)
  {
    field_of_view_ = field_of_view;
  }

  void Camera::set_z_near(const float z_near)
  {
    z_near_ = z_near;
  }

  void Camera::set_z_far(const float z_far)
  {
    z_far_ = z_far;
  }

  void Camera::set_aspect_ratio(const float aspect_ratio)
  {
    aspect_ratio_ = aspect_ratio;
  }
}
