// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

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

  inline glm::vec<2, T> getValue() const;

  inline void setValue(glm::vec<2, T> value);

  glm::vec<2, T> _value;
};

template<typename T>
GeoVector<T>::GeoVector(T x, T y) : _value(glm::vec2(x, y)) {
}

template<typename T>
GeoVector<T>::GeoVector(glm::vec<2, T> value) : _value(value) {
}

template<typename T>
T GeoVector<T>::getX() const {
  return getValue().x;
}

template<typename T>
void GeoVector<T>::setX(T value) {
  _value.x = value;
}

template<typename T>
T GeoVector<T>::getY() const {
  return getValue().y;
}

template<typename T>
void GeoVector<T>::setY(T value) {
  _value.y = value;
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const GeoVector<T>& other) const {
  return GeoVector<T>(getValue() + other.getValue());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const GeoVector<T>& other) const {
  return GeoVector<T>(getValue() - other.getValue());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const GeoVector<T>& other) const {
  return GeoVector<T>(getValue() * other.getValue());
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const GeoVector<T>& other) const {
  return GeoVector<T>(getValue() / other.getValue());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const T other) const {
  return GeoVector<T>(getValue() + other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const T other) const {
  return GeoVector<T>(getValue() - other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const T other) const {
  return GeoVector<T>(getValue() * other);
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const T other) const {
  return GeoVector<T>(getValue() / other);
}
template<typename T>
GeoVector<T>::GeoVector() {

}
template<typename T>
void GeoVector<T>::rotateToAngleAroundPoint(const T angleRotationValue, const GeoVector<T>& point) {
  setValue(glm::rotate((getValue() - point.getValue()), glm::radians(angleRotationValue)) + point.getValue());
}

template<typename T>
inline glm::vec<2, T> GeoVector<T>::getValue() const {
  return _value;
}

template<typename T>
inline void GeoVector<T>::setValue(glm::vec<2, T> value) {
  _value = value;
}

}

#endif //NOVELRT_COORDINATEVECTOR_H
