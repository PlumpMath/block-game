#ifndef BLOCK_GAME_GENERAL_VECTOR_H_
#define BLOCK_GAME_GENERAL_VECTOR_H_

#include <cassert>
#include <initializer_list>
#include <stdexcept>

#include <json/json.h>

namespace block_game
{
  template<int dimensions>
  class Vector
  {
  public:
    static_assert(dimensions > 0, "Vector with nonpositive number of dimensions");

    Vector();
    Vector(const std::initializer_list<float>& initial_components);
    Vector(const Json::Value& value);

    float operator[](int i) const;
    float& operator[](int i);

    Vector<dimensions> operator+(const Vector<dimensions>& vector) const;
    Vector<dimensions> operator-(const Vector<dimensions>& vector) const;
    Vector<dimensions> operator*(float scalar) const;
    Vector<dimensions> operator/(float scalar) const;

    Vector<dimensions>& operator+=(const Vector<dimensions>& vector);
    Vector<dimensions>& operator-=(const Vector<dimensions>& vector);
    Vector<dimensions>& operator*=(float scalar);
    Vector<dimensions>& operator/=(float scalar);

    void RotateX(float angle); // Rotate around the x-axis
    void RotateY(float angle); // Rotate around the y-axis
    void RotateZ(float angle); // Rotate around the z-axis

  private:
    float components[dimensions];
  };

  template<int dimensions>
  Vector<dimensions> operator*(float scalar, const Vector<dimensions>& vector);
  template<int dimensions>
  Vector<dimensions> operator/(float scalar, const Vector<dimensions>& vector);

  template<int dimensions>
  Vector<dimensions>::Vector()
  {
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] = 0.0F;
    }
  }

  template<int dimensions>
  Vector<dimensions>::Vector(const std::initializer_list<float>& initial_components)
  {
    assert(initial_components.size() == dimensions);
    int i = 0;
    for (const float component : initial_components)
    {
      components[i] = component;
      ++i;
    }
  }

  template<int dimensions>
  Vector<dimensions>::Vector(const Json::Value& value)
  {
    if (!value.isArray())
    {
      throw std::runtime_error{"non-array JSON value cannot be used to construct Vector"};
    }
    else if (value.size() != dimensions)
    {
      throw std::runtime_error{"JSON value size does not match number of dimensions in Vector"};
    }
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] = value[i].asFloat();
    }
  }

  template<int dimensions>
  float Vector<dimensions>::operator[](const int i) const
  {
    assert(i >= 0 && i < dimensions);
    return components[i];
  }

  template<int dimensions>
  float& Vector<dimensions>::operator[](const int i)
  {
    assert(i >= 0 && i < dimensions);
    return components[i];
  }

  template<int dimensions>
  Vector<dimensions> Vector<dimensions>::operator+(const Vector<dimensions>& vector) const
  {
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      new_vector[i] = components[i] + vector[i];
    }
    return new_vector;
  }

  template<int dimensions>
  Vector<dimensions> Vector<dimensions>::operator-(const Vector<dimensions>& vector) const
  {
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      new_vector[i] = components[i] - vector[i];
    }
    return new_vector;
  }

  template<int dimensions>
  Vector<dimensions> Vector<dimensions>::operator*(const float scalar) const
  {
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      new_vector[i] = components[i] * scalar;
    }
    return new_vector;
  }

  template<int dimensions>
  Vector<dimensions> Vector<dimensions>::operator/(const float scalar) const
  {
    assert(scalar != 0.0F);
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      new_vector[i] = components[i] / scalar;
    }
    return new_vector;
  }

  template<int dimensions>
  Vector<dimensions>& Vector<dimensions>::operator+=(const Vector<dimensions>& vector)
  {
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] += vector[i];
    }
    return *this;
  }

  template<int dimensions>
  Vector<dimensions>& Vector<dimensions>::operator-=(const Vector<dimensions>& vector)
  {
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] -= vector[i];
    }
    return *this;
  }

  template<int dimensions>
  Vector<dimensions>& Vector<dimensions>::operator*=(const float scalar)
  {
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] *= scalar;
    }
    return *this;
  }

  template<int dimensions>
  Vector<dimensions>& Vector<dimensions>::operator/=(const float scalar)
  {
    assert(scalar != 0.0F);
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] /= scalar;
    }
    return *this;
  }

  template<int dimensions>
  void Vector<dimensions>::RotateX(const float angle)
  {
    static_assert(dimensions >= 3, "rotate Vector in x-axis without y-axis and z-axis");

    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_y{components[1] * cosine - components[2] * sine};
    const float new_z{components[1] * sine + components[2] * cosine};

    components[1] = new_y;
    components[2] = new_z;
  }

  template<int dimensions>
  void Vector<dimensions>::RotateY(const float angle)
  {
    static_assert(dimensions >= 3, "rotate Vector in y-axis without x-axis and z-axis");

    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_x{components[2] * sine + components[0] * cosine};
    const float new_z{components[2] * cosine - components[0] * sine};

    components[0] = new_x;
    components[2] = new_z;
  }

  template<int dimensions>
  void Vector<dimensions>::RotateZ(const float angle)
  {
    static_assert(dimensions >= 2, "rotate Vector in z-axis without x-axis and y-axis");

    const float sine{sin(angle)};
    const float cosine{cos(angle)};

    const float new_x{components[0] * cosine - components[1] * sine};
    const float new_y{components[0] * sine + components[1] * cosine};

    components[0] = new_x;
    components[1] = new_y;
  }

  template<int dimensions>
  Vector<dimensions> operator*(const float scalar, const Vector<dimensions>& vector)
  {
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      new_vector[i] = scalar * vector[i];
    }
    return new_vector;
  }

  template<int dimensions>
  Vector<dimensions> operator/(const float scalar, const Vector<dimensions>& vector)
  {
    Vector<dimensions> new_vector;
    for (int i = 0; i < dimensions; ++i)
    {
      assert(vector[i] != 0.0F);
      new_vector[i] = scalar / vector[i];
    }
    return new_vector;
  }
}

#endif
