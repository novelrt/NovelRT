// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_COORDINATEVECTOR_H
#define NOVELRT_COORDINATEVECTOR_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace NovelRT {
  template<typename T>
  class GeoVector {

  private:
    glm::vec<2, T> _value;

    GeoVector(glm::vec<2, T> value) : _value(value) {}

    inline glm::vec<2, T> getValue() const {
      return _value;
    }
    inline void setValue(glm::vec<2, T> value) {
      _value = value;
    }

  public:
    GeoVector() {}
    GeoVector(T x, T y) : _value(glm::vec2(x, y)) {}

    T getX() const {
      return getValue().x;
    }
    void setX(T value) {
      _value.x = value;
    }

    T getY() const {
      return getValue().y;
    }
    void setY(T value) {
      _value.y = value;
    }

    void rotateToAngleAroundPoint(T angleRotationValue, const GeoVector<T>& point) {
      setValue(glm::rotate((getValue() - point.getValue()), glm::radians(angleRotationValue)) + point.getValue());
    }

    inline GeoVector<T> operator+(const GeoVector<T>& other) const {
      return GeoVector<T>(getValue() + other.getValue());
    }
    inline GeoVector<T> operator-(const GeoVector<T>& other) const {
      return GeoVector<T>(getValue() - other.getValue());
    }
    inline GeoVector<T> operator*(const GeoVector<T>& other) const {
      return GeoVector<T>(getValue() * other.getValue());
    }
    inline GeoVector<T> operator/(const GeoVector<T>& other) const {
      return GeoVector<T>(getValue() / other.getValue());
    }

    inline GeoVector<T> operator+(T other) const {
      return GeoVector<T>(getValue() + other);
    }
    inline GeoVector<T> operator-(T other) const {
      return GeoVector<T>(getValue() - other);
    }
    inline GeoVector<T> operator*(T other) const {
      return GeoVector<T>(getValue() * other);
    }
    inline GeoVector<T> operator/(T other) const {
      return GeoVector<T>(getValue() / other);
    }
  };
}

#endif //NOVELRT_COORDINATEVECTOR_H
