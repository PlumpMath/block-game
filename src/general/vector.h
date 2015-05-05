#ifndef BLOCK_GAME_GENERAL_VECTOR_H_
#define BLOCK_GAME_GENERAL_VECTOR_H_

#include <initializer_list>

namespace block_game
{
  template<int dimensions>
  struct Vector
  {
    Vector();
    Vector(const std::initializer_list<float>&);

    float operator[](const int) const;
    float& operator[](const int);

    Vector<dimensions> operator+(const Vector<dimensions>&) const;
    Vector<dimensions> operator-(const Vector<dimensions>&) const;
    Vector<dimensions> operator*(const float) const;
    Vector<dimensions> operator/(const float) const;

    Vector<dimensions>& operator+=(const Vector<dimensions>&);
    Vector<dimensions>& operator-=(const Vector<dimensions>&);
    Vector<dimensions>& operator*=(const float);
    Vector<dimensions>& operator/=(const float);

    void RotateX(const float); // Rotate around the x-axis
    void RotateY(const float); // Rotate around the y-axis
    void RotateZ(const float); // Rotate around the z-axis

    float components[dimensions];
  };

  template<int dimensions>
  Vector<dimensions> operator*(const float, const Vector<dimensions>&);
  template<int dimensions>
  Vector<dimensions> operator/(const float, const Vector<dimensions>&);

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
    int i = 0;
    for (const float component : initial_components)
    {
      components[i] = component;
      ++i;
    }
  }

  template<int dimensions>
  float Vector<dimensions>::operator[](const int i) const
  {
    return components[i];
  }

  template<int dimensions>
  float& Vector<dimensions>::operator[](const int i)
  {
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
    for (int i = 0; i < dimensions; ++i)
    {
      components[i] /= scalar;
    }
    return *this;
  }

  template<int dimensions>
  void Vector<dimensions>::RotateX(const float angle)
  {
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
      new_vector[i] = scalar / vector[i];
    }
    return new_vector;
  }
}

#endif
