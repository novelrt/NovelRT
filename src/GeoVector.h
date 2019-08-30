//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_COORDINATEVECTOR_H
#define NOVELRT_COORDINATEVECTOR_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace NovelRT {
template<typename T>
class GeoVector {
public:
  GeoVector();
  GeoVector(T x, T y);

  T getX() const;

  void setX(T value);

  T getY() const;

  void setY(T value);

  inline GeoVector<T> operator+(const GeoVector<T>& other) const;

  inline GeoVector<T> operator-(const GeoVector<T>& other) const;

  inline GeoVector<T> operator*(const GeoVector<T>& other) const;

  inline GeoVector<T> operator/(const GeoVector<T>& other) const;

  inline GeoVector<T> operator+(const T other) const;

  inline GeoVector<T> operator-(const T other) const;

  inline GeoVector<T> operator*(const T other) const;

  inline GeoVector<T> operator/(const T other) const;

  void rotateToAngleAroundPoint(const T angleRotationValue, const GeoVector<T>& point);

private:
  GeoVector(glm::vec<2, T> value);

  glm::vec<2, T> _value;
};

template<typename T>
GeoVector<T>::GeoVector(T x, T y) {
  _value = glm::vec2(x, y);
}

template<typename T>
GeoVector<T>::GeoVector(glm::vec<2, T> value) : _value(value) {
}

template<typename T>
T GeoVector<T>::getX() const {
  return _value.x;
}

template<typename T>
void GeoVector<T>::setX(T value) {
  _value.x = value;
}

template<typename T>
T GeoVector<T>::getY() const {
  return _value.y;
}

template<typename T>
void GeoVector<T>::setY(T value) {
  _value.y = value;
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const GeoVector<T>& other) const {
  return GeoVector<T>(_value + other._value);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const GeoVector<T>& other) const {
  return GeoVector<T>(_value - other._value);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const GeoVector<T>& other) const {
  return GeoVector<T>(_value * other._value);
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const GeoVector<T>& other) const {
  return GeoVector<T>(_value / other._value);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const T other) const {
  return GeoVector<T>(_value + other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const T other) const {
  return GeoVector<T>(_value - other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const T other) const {
  return GeoVector<T>(_value * other);
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const T other) const {
  return GeoVector<T>(_value / other);
}
template<typename T>
GeoVector<T>::GeoVector() {

}
template<typename T>
void GeoVector<T>::rotateToAngleAroundPoint(const T angleRotationValue, const GeoVector<T>& point) {
  _value = glm::rotate((_value - point._value), glm::radians(angleRotationValue)) + point._value;
}

}

#endif //NOVELRT_COORDINATEVECTOR_H
