// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See License.md in the repository root for more information.

#ifndef NOVELRT_COORDINATEVECTOR_H
#define NOVELRT_COORDINATEVECTOR_H
#include <glm/glm.hpp>
#include <glm/gtx/rotate_vector.hpp>

namespace NovelRT {
template<typename T>
class GeoVector {
  friend class NovelRenderObject;
  template<typename U>
  friend class GeoMatrix4;
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
  GeoVector(glm::vec<4, T> value);

  inline glm::vec<2, T> getVec2Value() const;

  inline void setVec2Value(glm::vec<2, T> value);

  inline glm::vec<4, T> getVec4Value() const;

  inline void setVec4Value(glm::vec<4, T> value);

  glm::vec<4, T> _value;
};

template<typename T>
GeoVector<T>::GeoVector(T x, T y) : _value(glm::vec<4, T>(x, y, 0, 0)) {
}

template<typename T>
GeoVector<T>::GeoVector(glm::vec<2, T> value) : _value(glm ::vec<4, T>(value, 0, 0)) {
}

template<typename T>
GeoVector<T>::GeoVector(glm::vec<4, T> value) : _value(value) {

}

template<typename T>
T GeoVector<T>::getX() const {
  return getVec2Value().x;
}

template<typename T>
void GeoVector<T>::setX(T value) {
  _value.x = value;
}

template<typename T>
T GeoVector<T>::getY() const {
  return getVec2Value().y;
}

template<typename T>
void GeoVector<T>::setY(T value) {
  _value.y = value;
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const GeoVector<T>& other) const {
  return GeoVector<T>(getVec2Value() + other.getVec2Value());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const GeoVector<T>& other) const {
  return GeoVector<T>(getVec2Value() - other.getVec2Value());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const GeoVector<T>& other) const {
  return GeoVector<T>(getVec2Value() * other.getVec2Value());
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const GeoVector<T>& other) const {
  return GeoVector<T>(getVec2Value() / other.getVec2Value());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const T other) const {
  return GeoVector<T>(getVec2Value() + other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const T other) const {
  return GeoVector<T>(getVec2Value() - other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const T other) const {
  return GeoVector<T>(getVec2Value() * other);
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const T other) const {
  return GeoVector<T>(getVec2Value() / other);
}
template<typename T>
GeoVector<T>::GeoVector() {

}
template<typename T>
void GeoVector<T>::rotateToAngleAroundPoint(const T angleRotationValue, const GeoVector<T>& point) {
  setVec2Value(
      glm::rotate((getVec2Value() - point.getVec2Value()), glm::radians(angleRotationValue)) + point.getVec2Value());
}

template<typename T>
inline glm::vec<2, T> GeoVector<T>::getVec2Value() const {
  return glm::vec<2, T>(_value.x, _value.y);
}

template<typename T>
inline void GeoVector<T>::setVec2Value(glm::vec<2, T> value) {
  _value.x = value.x;
  _value.y = value.y;
}

template<typename T>
glm::vec<4, T> GeoVector<T>::getVec4Value() const {
  return _value;
}

template<typename T>
void GeoVector<T>::setVec4Value(glm::vec<4, T> value) {
  _value = value;
}

}

#endif //NOVELRT_COORDINATEVECTOR_H
