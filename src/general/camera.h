#ifndef BLOCK_GAME_GENERAL_CAMERA_H_
#define BLOCK_GAME_GENERAL_CAMERA_H_

#include <json/json.h>

#include "general/matrix.h"
#include "general/vector.h"

namespace block_game {
class Camera {
public:
  Camera();
  Camera(const Json::Value& value);

  Vector<3> GetPosition() const;

  float GetYaw() const;
  float GetPitch() const;
  float GetRoll() const;

  float GetFieldOfView() const;
  float GetZNear() const;
  float GetZFar() const;
  float GetAspectRatio() const;

  void SetPosition(const Vector<3>& position);

  void SetYaw(float yaw);
  void SetPitch(float pitch);
  void SetRoll(float roll);

  void SetFieldOfView(float field_of_view);
  void SetZNear(float z_near);
  void SetZFar(float z_far);
  void SetAspectRatio(float aspect_ratio);

  Matrix<4> GetMatrix() const;

private:
  Vector<3> position_;

  float yaw_;
  float pitch_;
  float roll_;

  float field_of_view_;
  float z_near_;
  float z_far_;
  float aspect_ratio_;
};
}

#endif
