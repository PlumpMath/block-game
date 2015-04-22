#include "general/camera.h"

#include <cmath>

#include "general/matrix.h"
#include "general/vector_3f.h"

namespace block_game
{
  Camera::Camera() : field_of_view_{1.0F}, z_near_{0.1F}, z_far_{1.0F}, aspect_ratio_{1.0F}
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

  Matrix<4> Camera::GetMatrix() const
  {
    const float x_scale{1 / tan(field_of_view_ / 2)};
    const float y_scale{aspect_ratio_ * x_scale};
    const float z_average{(z_near_ + z_far_) / 2};
    const float z_half_distance{(z_far_ - z_near_) / 2};

    Matrix<4> translate;
    translate[0][3] = -position_.x;
    translate[1][3] = -position_.y;
    translate[2][3] = -position_.z;

    Matrix<4> rotate;
    rotate.RotateZ(-rotation_.z);
    rotate.RotateX(-rotation_.x);
    rotate.RotateY(-rotation_.y);

    Matrix<4> scale;
    scale[0][0] = x_scale;
    scale[1][1] = y_scale;

    Matrix<4> z_translate;
    z_translate[2][3] = -z_average;

    Matrix<4> z_scale;
    z_scale[2][2] = 1 / z_half_distance;

    Matrix<4> project;
    project[3][2] = z_average;
    project[3][3] = z_half_distance;

    return project * z_scale * z_translate * scale * rotate * translate;
  }
}
