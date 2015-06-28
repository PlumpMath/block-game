#ifndef BLOCK_GAME_GENERAL_VECTOR_H_
#define BLOCK_GAME_GENERAL_VECTOR_H_

#include <cassert>
#include <cmath>
#include <initializer_list>
#include <stdexcept>

#include <json/json.h>

namespace block_game {
template<int dimensions> class Vector {
public:
  static_assert(0 < dimensions, "Vector with nonpositive number of dimensions");

  Vector();
  Vector(const std::initializer_list<float>& initial_components);
  Vector(const Json::Value& value);

  float operator[](int i) const;
  float& operator[](int i);

  bool operator==(const Vector<dimensions>& vector) const;
  bool operator!=(const Vector<dimensions>& vector) const;

  Vector<dimensions> operator-() const;

  Vector<dimensions> operator+(const Vector<dimensions>& vector) const;
  Vector<dimensions> operator-(const Vector<dimensions>& vector) const;
  Vector<dimensions> operator*(float scalar) const;
  Vector<dimensions> operator/(float scalar) const;

  Vector<dimensions>& operator+=(const Vector<dimensions>& vector);
  Vector<dimensions>& operator-=(const Vector<dimensions>& vector);
  Vector<dimensions>& operator*=(float scalar);
  Vector<dimensions>& operator/=(float scalar);

  bool ContainsZero() const;
  bool IsInColorRange() const;

  void RotateAboutX(float angle);
  void RotateAboutY(float angle);
  void RotateAboutZ(float angle);

private:
  float components[dimensions];
};

template<int dimensions> Vector<dimensions> operator*(float scalar, const Vector<dimensions>& vector);
template<int dimensions> Vector<dimensions> operator/(float scalar, const Vector<dimensions>& vector);

template<int dimensions> Vector<dimensions>::Vector() {
  for (int i{0}; i < dimensions; ++i) {
    components[i] = 0.0F;
  }
}

template<int dimensions> Vector<dimensions>::Vector(const std::initializer_list<float>& initial_components) {
  assert(initial_components.size() == dimensions);

  int i{0};
  for (const float component : initial_components) {
    components[i] = component;
    ++i;
  }
}

template<int dimensions> Vector<dimensions>::Vector(const Json::Value& value) {
  if (!value.isArray()) {
    throw std::runtime_error{"non-array JSON value cannot be used to construct Vector"};
  } else if (value.size() != dimensions) {
    throw std::runtime_error{"JSON value size does not match number of dimensions in Vector"};
  } else {
    for (Json::ArrayIndex i{0}; i < dimensions; ++i) {
      if (!value[i].isNumeric()) {
        throw std::runtime_error{"non-numeric JSON value cannot be converted to Vector member"};
      }
    }
  }

  for (Json::ArrayIndex i{0}; i < dimensions; ++i) {
    components[i] = value[i].asFloat();
  }
}

template<int dimensions> float Vector<dimensions>::operator[](const int i) const {
  assert(0 <= i && i < dimensions);

  return components[i];
}

template<int dimensions> float& Vector<dimensions>::operator[](const int i) {
  assert(0 <= i && i < dimensions);

  return components[i];
}

template<int dimensions> bool Vector<dimensions>::operator==(const Vector<dimensions>& vector) const {
  for (int i{0}; i < dimensions; ++i) {
    if (components[i] != vector[i]) {
      return false;
    }
  }
  return true;
}

template<int dimensions> bool Vector<dimensions>::operator!=(const Vector<dimensions>& vector) const {
  return !(*this == vector);
}

template<int dimensions> Vector<dimensions> Vector<dimensions>::operator-() const {
  return *this * -1.0F;
}

template<int dimensions> Vector<dimensions> Vector<dimensions>::operator+(const Vector<dimensions>& vector) const {
  Vector<dimensions> new_vector;
  for (int i{0}; i < dimensions; ++i) {
    new_vector[i] = components[i] + vector[i];
  }
  return new_vector;
}

template<int dimensions> Vector<dimensions> Vector<dimensions>::operator-(const Vector<dimensions>& vector) const {
  return *this + -vector;
}

template<int dimensions> Vector<dimensions> Vector<dimensions>::operator*(const float scalar) const {
  Vector<dimensions> new_vector;
  for (int i{0}; i < dimensions; ++i) {
    new_vector[i] = components[i] * scalar;
  }
  return new_vector;
}

template<int dimensions> Vector<dimensions> Vector<dimensions>::operator/(const float scalar) const {
  assert(scalar != 0.0F);

  Vector<dimensions> new_vector;
  for (int i{0}; i < dimensions; ++i) {
    new_vector[i] = components[i] / scalar;
  }
  return new_vector;
}

template<int dimensions> Vector<dimensions>& Vector<dimensions>::operator+=(const Vector<dimensions>& vector) {
  return *this = *this + vector;
}

template<int dimensions> Vector<dimensions>& Vector<dimensions>::operator-=(const Vector<dimensions>& vector) {
  return *this = *this - vector;
}

template<int dimensions> Vector<dimensions>& Vector<dimensions>::operator*=(const float scalar) {
  return *this = *this * scalar;
}

template<int dimensions> Vector<dimensions>& Vector<dimensions>::operator/=(const float scalar) {
  assert(scalar != 0.0F);

  return *this = *this / scalar;
}

template<int dimensions> bool Vector<dimensions>::ContainsZero() const {
  for (const auto component : components) {
    if (component == 0.0F) {
      return true;
    }
  }
  return false;
}

template<int dimensions> bool Vector<dimensions>::IsInColorRange() const {
  for (const auto component : components) {
    if (component < 0.0F || 1.0F < component) {
      return false;
    }
  }
  return true;
}

template<int dimensions> void Vector<dimensions>::RotateAboutX(const float angle) {
  static_assert(3 <= dimensions, "rotate Vector about x-axis without y-axis and z-axis");

  const float sine{std::sin(angle)};
  const float cosine{std::cos(angle)};

  const float new_y{components[1] * cosine - components[2] * sine};
  const float new_z{components[1] * sine + components[2] * cosine};

  components[1] = new_y;
  components[2] = new_z;
}

template<int dimensions> void Vector<dimensions>::RotateAboutY(const float angle) {
  static_assert(3 <= dimensions, "rotate Vector about y-axis without x-axis and z-axis");

  const float sine{std::sin(angle)};
  const float cosine{std::cos(angle)};

  const float new_x{components[2] * sine + components[0] * cosine};
  const float new_z{components[2] * cosine - components[0] * sine};

  components[0] = new_x;
  components[2] = new_z;
}

template<int dimensions> void Vector<dimensions>::RotateAboutZ(const float angle) {
  static_assert(2 <= dimensions, "rotate Vector about z-axis without x-axis and y-axis");

  const float sine{std::sin(angle)};
  const float cosine{std::cos(angle)};

  const float new_x{components[0] * cosine - components[1] * sine};
  const float new_y{components[0] * sine + components[1] * cosine};

  components[0] = new_x;
  components[1] = new_y;
}

template<int dimensions> Vector<dimensions> operator*(const float scalar, const Vector<dimensions>& vector) {
  return vector * scalar;
}

template<int dimensions> Vector<dimensions> operator/(const float scalar, const Vector<dimensions>& vector) {
  assert(!vector.ContainsZero());

  Vector<dimensions> new_vector;
  for (int i{0}; i < dimensions; ++i) {
    new_vector[i] = scalar / vector[i];
  }
  return new_vector;
}
}

#endif
