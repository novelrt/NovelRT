// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_GEOMATRIX4_H
#define NOVELRT_GEOMATRIX4_H
#include <glm/glm.hpp>
#include "GeoVector.h"

namespace NovelRT {

  template<typename T>
  class GeoMatrix4 {
    friend class NovelRenderObject;
    friend class NovelImageRect;
    friend class NovelBasicFillRect;
    friend class NovelTextRect;
    friend class NovelRenderingService;
  private:
    glm::mat<4, 4, T> _value;

    inline glm::mat4 getUnderlyingMatrix() const {
      return _value;
    }

    explicit GeoMatrix4(glm::mat4 matrix) {
      _value = matrix;
    }

  public:
    GeoMatrix4() {}

    GeoMatrix4(GeoVector<T> x,
      GeoVector<T> y,
      GeoVector<T> z,
      GeoVector<T> w) {
      setX(x);
      setY(y);
      setZ(z);
      setW(w);
    }

    inline GeoVector<T> getX() const {
      return GeoVector<T>(_value[0]);
    }

    inline void setX(GeoVector<T> value) {
      _value[0] = value.getVec4Value();
    }

    inline GeoVector<T> getY() const {
      return GeoVector<T>(_value[1]);
    }

    inline void setY(GeoVector<T> value) {
      _value[1] = value.getVec4Value();
    }

    inline GeoVector<T> getZ() const {
      return GeoVector<T>(_value[2]);
    }

    inline void setZ(GeoVector<T> value) {
      _value[2] = value.getVec4Value();
    }

    inline GeoVector<T> getW() const {
      return GeoVector<T>(_value[3]);
    }

    inline void setW(GeoVector<T> value) {
      _value[3] = value.getVec4Value();
    }

    inline GeoMatrix4<T> operator+(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(getUnderlyingMatrix() + other.getUnderlyingMatrix());
    }

    inline GeoMatrix4<T> operator-(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(getUnderlyingMatrix() - other.getUnderlyingMatrix());
    }

    inline GeoMatrix4<T> operator*(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(getUnderlyingMatrix() * other.getUnderlyingMatrix());
    }

    inline GeoMatrix4<T> operator/(const GeoMatrix4<T>& other) const {
      return GeoMatrix4<T>(getUnderlyingMatrix() / other.getUnderlyingMatrix());
    }

    static GeoMatrix4<T> getDefaultIdentity() {
      return GeoMatrix4<T>(glm::identity<glm::mat4>());
    }
  };
}

#endif //NOVELRT_GEOMATRIX4_H
