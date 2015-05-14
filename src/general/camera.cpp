#include "general/camera.h"

#include <algorithm>
#include <cassert>
#include <cmath>

#include <json/json.h>

#include "general/math.h"
#include "general/matrix.h"
#include "general/vector.h"

namespace block_game
{
Camera::Camera() : yaw_{0.0F}, pitch_{0.0F}, roll_{0.0F}, field_of_view_{1.0F}, z_near_{0.1F}, z_far_{1.0F}, aspect_ratio_{1.0F}
{}

Camera::Camera(const Json::Value& value) : Camera{}
{
  if (value.isMember("position"))
  {
    position_ = value["position"];
  }

  yaw_ = value.get("yaw", yaw_).asFloat();
  pitch_ = value.get("pitch", pitch_).asFloat();
  roll_ = value.get("roll", roll_).asFloat();

  field_of_view_ = value.get("fieldOfView", field_of_view_).asFloat();
  z_near_ = value.get("zNear", z_near_).asFloat();
  z_far_ = value.get("zFar", z_far_).asFloat();
  aspect_ratio_ = value.get("aspectRatio", aspect_ratio_).asFloat();
}

Vector<3> Camera::GetPosition() const
{
  return position_;
}

float Camera::GetYaw() const
{
  return yaw_;
}

float Camera::GetPitch() const
{
  return pitch_;
}

float Camera::GetRoll() const
{
  return roll_;
}

float Camera::GetFieldOfView() const
{
  return field_of_view_;
}

float Camera::GetZNear() const
{
  return z_near_;
}

float Camera::GetZFar() const
{
  return z_far_;
}

float Camera::GetAspectRatio() const
{
  return aspect_ratio_;
}

void Camera::SetPosition(const Vector<3>& position)
{
  position_ = position;
}

void Camera::SetYaw(const float yaw)
{
  yaw_ = fmod(yaw, 2 * kPiF);
}

void Camera::SetPitch(const float pitch)
{
  pitch_ = std::min<float>(std::max<float>(0.0F, pitch), kPiF);
}

void Camera::SetRoll(const float roll)
{
  roll_ = fmod(roll, 2 * kPiF);
}

void Camera::SetFieldOfView(const float field_of_view)
{
  assert(field_of_view > 0.0F && field_of_view < kPiF);

  field_of_view_ = field_of_view;
}

void Camera::SetZNear(const float z_near)
{
  assert(z_near > 0.0F);

  z_near_ = z_near;
}

void Camera::SetZFar(const float z_far)
{
  assert(z_far > 0.0F);

  z_far_ = z_far;
}

void Camera::SetAspectRatio(const float aspect_ratio)
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
