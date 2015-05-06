#ifndef BLOCK_GAME_GENERAL_CAMERA_H_
#define BLOCK_GAME_GENERAL_CAMERA_H_

#include "general/matrix.h"
#include "general/vector.h"

namespace block_game
{
  class Camera
  {
  public:
    Camera();

    Vector<3> GetPosition() const;

    float GetYaw() const;
    float GetPitch() const;
    float GetRoll() const;

    float GetFieldOfView() const;
    float GetZNear() const;
    float GetZFar() const;
    float GetAspectRatio() const;

    void SetPosition(const Vector<3>&);

    void SetYaw(const float);
    void SetPitch(const float);
    void SetRoll(const float);

    void SetFieldOfView(const float);
    void SetZNear(const float);
    void SetZFar(const float);
    void SetAspectRatio(const float);

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
