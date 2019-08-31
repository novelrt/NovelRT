//
// Created by matth on 15/12/2018.
//

#ifndef NOVELRT_COORDINATEVECTOR_H
#define NOVELRT_COORDINATEVECTOR_H
#define _USE_MATH_DEFINES
#include <math.h>

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
  T _x;
  T _y;
};

template<typename T>
GeoVector<T>::GeoVector(T x, T y) {
  _x = x;
  _y = y;
}

template<typename T>
T GeoVector<T>::getX() const {
  return _x;
}

template<typename T>
void GeoVector<T>::setX(T value) {
  GeoVector::_x = value;
}

template<typename T>
T GeoVector<T>::getY() const {
  return _y;
}

template<typename T>
void GeoVector<T>::setY(T value) {
  GeoVector::_y = value;
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const GeoVector<T>& other) const {
  return GeoVector<T>(GeoVector<T>::getX() + other.getX(), GeoVector<T>::getY() + other.getY());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const GeoVector<T>& other) const {
  return GeoVector<T>(GeoVector<T>::getX() - other.getX(), GeoVector<T>::getY() - other.getY());
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const GeoVector<T>& other) const {
  return GeoVector<T>(GeoVector<T>::getX() * other.getX(), GeoVector<T>::getY() * other.getY());
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const GeoVector<T>& other) const {
  return GeoVector<T>(GeoVector<T>::getX() / other, GeoVector<T>::getY() / other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator+(const T other) const {
  return GeoVector<T>(GeoVector<T>::getX() + other, GeoVector<T>::getY() + other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator-(const T other) const {
  return GeoVector<T>(GeoVector<T>::getX() - other, GeoVector<T>::getY() - other);
}

template<typename T>
inline GeoVector<T> GeoVector<T>::operator*(const T other) const {
  return GeoVector<T>(GeoVector<T>::getX() * other, GeoVector<T>::getY() * other);
}

template<typename T>
GeoVector<T> GeoVector<T>::operator/(const T other) const {
  return GeoVector<T>(GeoVector<T>::getX() / other, GeoVector<T>::getY() / other);
}
template<typename T>
GeoVector<T>::GeoVector() {

}
template<typename T>
void GeoVector<T>::rotateToAngleAroundPoint(const T angleRotationValue, const GeoVector<T>& point) {
  auto angle = angleRotationValue * (M_PI/180);

  auto px = getX();
  auto py = getY();
  auto ox = point.getX();
  auto oy = point.getY();
  
  auto x = px - ox;
  auto y = py - oy;

  auto cos0 = cosf(angle);
  auto sin0 = sinf(angle);

  setX(((x * cos0) - (y * sin0)) + ox);
  setY(((y * cos0) + (x * sin0)) + oy);
}

}

#endif //NOVELRT_COORDINATEVECTOR_H
