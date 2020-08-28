// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_MATHS_GEOMATRIX4_H
#define NOVELRT_MATHS_GEOMATRIX4_H

#ifndef NOVELRT_H
#error Please do not include this directly. Use the centralised header (NovelRT.h) instead!
#endif

#include "BaseGeoMatrix4x4F.h"

namespace NovelRT::Maths {

  class GeoMatrix4x4F : public NovelRTGeoMatrix4x4F {
    friend class Graphics::RenderObject;
    friend class Graphics::ImageRect;
    friend class Graphics::BasicFillRect;
    friend class Graphics::TextRect;
    friend class Graphics::RenderingService;
    friend class Graphics::Camera;

  private:
    inline const glm::mat4& underlyingMatrix() const {
      return *reinterpret_cast<const glm::mat4*>(this);
    }

    inline glm::mat4& underlyingMatrix() {
      return *reinterpret_cast<glm::mat4*>(this);
    }

    explicit GeoMatrix4x4F(glm::mat4 matrix) {
      x = *reinterpret_cast<NovelRTGeoVector4F*>(&matrix[0]);
      y = *reinterpret_cast<NovelRTGeoVector4F*>(&matrix[1]);
      z = *reinterpret_cast<NovelRTGeoVector4F*>(&matrix[2]);
      w = *reinterpret_cast<NovelRTGeoVector4F*>(&matrix[3]);
    }

  public:
    GeoMatrix4x4F() {}

    GeoMatrix4x4F(GeoVector4F x,
      GeoVector4F y,
      GeoVector4F z,
      GeoVector4F w) : NovelRTGeoMatrix4x4F {
        x,
        y,
        z,
        w
      } {}

    inline bool operator==(const GeoMatrix4x4F& other) const {
      return underlyingMatrix() == other.underlyingMatrix();
    }

    inline bool operator!=(const GeoMatrix4x4F& other) const {
      return underlyingMatrix() != other.underlyingMatrix();
    }

    inline GeoMatrix4x4F operator+(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() + other.underlyingMatrix());
    }

    inline GeoMatrix4x4F operator-(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() - other.underlyingMatrix());
    }

    inline GeoMatrix4x4F operator*(const GeoMatrix4x4F& other) const {
      return GeoMatrix4x4F(underlyingMatrix() * other.underlyingMatrix());
    }

    inline GeoMatrix4x4F& operator+=(const GeoMatrix4x4F& other) {
      underlyingMatrix() += other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F& operator-=(const GeoMatrix4x4F& other) {
      underlyingMatrix() -= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F& operator*=(const GeoMatrix4x4F& other) {
      underlyingMatrix() *= other.underlyingMatrix();
      return *this;
    }

    inline GeoMatrix4x4F operator+(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() + other);
    }

    inline GeoMatrix4x4F operator-(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() - other);
    }

    inline GeoMatrix4x4F operator*(float other) const {
      return GeoMatrix4x4F(underlyingMatrix() * other);
    }

    inline GeoMatrix4x4F& operator+=(float other) {
      underlyingMatrix() += other;
      return *this;
    }

    inline GeoMatrix4x4F& operator-=(float other) {
      underlyingMatrix() -= other;
      return *this;
    }

    inline GeoMatrix4x4F& operator*=(float other) {
      underlyingMatrix() *= other;
      return *this;
    }

    static GeoMatrix4x4F getDefaultIdentity() {
      return GeoMatrix4x4F(glm::identity<glm::mat4>());
    }
  };
}

#endif //NOVELRT_MATHS_GEOMATRIX4_H
