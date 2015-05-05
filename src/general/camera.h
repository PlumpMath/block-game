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

    const Vector<3>& position() const;

    float yaw() const;
    float pitch() const;
    float roll() const;

    float field_of_view() const;
    float z_near() const;
    float z_far() const;
    float aspect_ratio() const;

    Vector<3>& position();

    void set_yaw(const float);
    void set_pitch(const float);
    void set_roll(const float);

    void set_field_of_view(const float);
    void set_z_near(const float);
    void set_z_far(const float);
    void set_aspect_ratio(const float);

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
