#include "general/camera.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include "general/math.h"
#include "general/matrix.h"
#include "general/vector.h"

namespace block_game
{
  Camera::Camera() : yaw_{0.0F}, pitch_{0.0F}, roll_{0.0F},
    field_of_view_{1.0F}, z_near_{0.1F}, z_far_{1.0F}, aspect_ratio_{1.0F}
  {}

  const Vector<3>& Camera::position() const
  {
    return position_;
  }

  float Camera::yaw() const
  {
    return yaw_;
  }

  float Camera::pitch() const
  {
    return pitch_;
  }

  float Camera::roll() const
  {
    return roll_;
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

  Vector<3>& Camera::position()
  {
    return position_;
  }

  void Camera::set_yaw(const float yaw)
  {
    yaw_ = fmod(yaw, 2 * kPiF);
  }

  void Camera::set_pitch(const float pitch)
  {
    pitch_ = std::min<float>(kPiF, std::max<float>(0.0F, pitch));
  }

  void Camera::set_roll(const float roll)
  {
    roll_ = fmod(roll, 2 * kPiF);
  }

  void Camera::set_field_of_view(const float field_of_view)
  {
    assert(field_of_view > 0.0F && field_of_view < kPiF);
    field_of_view_ = field_of_view;
  }

  void Camera::set_z_near(const float z_near)
  {
    assert(z_near > 0.0F);
    z_near_ = z_near;
  }

  void Camera::set_z_far(const float z_far)
  {
    assert(z_far > 0.0F);
    z_far_ = z_far;
  }

  void Camera::set_aspect_ratio(const float aspect_ratio)
  {
    assert(aspect_ratio > 0.0F);
    aspect_ratio_ = aspect_ratio;
  }

  Matrix<4> Camera::GetMatrix() const
  {
    Matrix<4> translation;
    translation[0][3] = -position_[0];
    translation[1][3] = -position_[1];
    translation[2][3] = -position_[2];

    Matrix<4> rotation;
    rotation.RotateZ(-yaw_);
    rotation.RotateX(-pitch_);
    rotation.RotateZ(-roll_);

    Matrix<4> projection;
    projection[0][0] = 1 / tan(field_of_view_ / 2);
    projection[1][1] = aspect_ratio_ / tan(field_of_view_ / 2);
    projection[2][2] = (z_far_ + z_near_) / (z_far_ - z_near_);
    projection[2][3] = -(2 * z_far_ * z_near_) / (z_far_ - z_near_);
    projection[3][2] = 1.0F;
    projection[3][3] = 0.0F;

    return projection * rotation * translation;
  }
}
