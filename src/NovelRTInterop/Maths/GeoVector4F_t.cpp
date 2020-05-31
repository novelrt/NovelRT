// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRTInterop/Maths/GeoVector4F_t.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoVector4F_t* GeoVector4F_create(float x, float y, float z, float w) {
    static Maths::GeoVector4<float> vector = { x, y, z, w };
    return reinterpret_cast<GeoVector4F_t*>(&vector);
  }

  GeoVector4F_t* GeoVector4F_createFromGeoVector2F(const GeoVector2F_t* vector) {
    Maths::GeoVector2<float>* cVector2 = reinterpret_cast<Maths::GeoVector2<float>*>(&vector);
    static Maths::GeoVector4<float> vec = { cVector2->getX(), cVector2->getY(), 0.0f, 0.0f };
    return reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  GeoVector4F_t* GeoVector4F_createFromGeoVector3F(const GeoVector3F_t* vector) {
    Maths::GeoVector3<float>* cVector3 = reinterpret_cast<Maths::GeoVector3<float>*>(&vector);
    static Maths::GeoVector4<float> vec = { cVector3->getX(), cVector3->getY(), cVector3->getZ(), 0.0f };
    return reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  const GeoVector4F_t* GeoVector4F_uniform(float value) {
    return GeoVector4F_create(value, value, value, value);
  }

  const GeoVector4F_t* GeoVector4F_zero() {
    return GeoVector4F_uniform(0.0f);
  }

  const GeoVector4F_t* GeoVector4F_one() {
    return GeoVector4F_uniform(1.0f);
  }

  float GeoVector4F_getX(GeoVector4F_t* gv) {
    return reinterpret_cast<Maths::GeoVector4<float>*>(&gv)->getX();
  }

  void GeoVector4F_setX(GeoVector4F_t* gv, float value) {
    static Maths::GeoVector4<float> vec = *(reinterpret_cast<Maths::GeoVector4<float>*>(&gv));
    vec.setX(value);
    gv = reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  float GeoVector4F_getY(GeoVector4F_t* gv) {
    return reinterpret_cast<Maths::GeoVector4<float>*>(&gv)->getY();
  }

  void GeoVector4F_setY(GeoVector4F_t* gv, float value) {
    static Maths::GeoVector4<float> vec = *(reinterpret_cast<Maths::GeoVector4<float>*>(&gv));
    vec.setY(value);
    gv = reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  float GeoVector4F_getZ(GeoVector4F_t* gv) {
    return reinterpret_cast<Maths::GeoVector4<float>*>(&gv)->getY();
  }

  void GeoVector4F_setZ(GeoVector4F_t* gv, float value) {
    static Maths::GeoVector4<float> vec = *(reinterpret_cast<Maths::GeoVector4<float>*>(&gv));
    vec.setZ(value);
    gv = reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  float GeoVector4F_getW(GeoVector4F_t* gv) {
    return reinterpret_cast<Maths::GeoVector4<float>*>(&gv)->getW();
  }

  void GeoVector4F_setW(GeoVector4F_t* gv, float value) {
    static Maths::GeoVector4<float> vec = *(reinterpret_cast<Maths::GeoVector4<float>*>(&gv));
    vec.setW(value);
    gv = reinterpret_cast<GeoVector4F_t*>(&vec);
  }

  void GeoVector4F_rotateToAngleAroundPoint(float angleRotationValue, GeoVector4F_t* vector, const GeoVector3F_t* point) noexcept {
    static Maths::GeoVector4<float> cVector = *reinterpret_cast<Maths::GeoVector4<float>*>(vector);
    const Maths::GeoVector3<float> cPoint = *reinterpret_cast<const Maths::GeoVector3<float>*>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);
    vector = reinterpret_cast<GeoVector4F_t*>(&cVector);
  }

  bool GeoVector4F_epsilonEquals(GeoVector4F_t* vector, const GeoVector4F_t* other, const GeoVector4F_t* epsilonValue) noexcept {
    Maths::GeoVector4<float>v1 = *reinterpret_cast<Maths::GeoVector4<float>*>(vector);
    Maths::GeoVector4<float>v2 = *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    Maths::GeoVector4<float>v3 = *reinterpret_cast<const Maths::GeoVector4<float>*>(epsilonValue);
    return v1.epsilonEquals(v2, v3);
  }

  GeoVector4F_t* GeoVector4F_getNormalised(GeoVector4F_t* gv) {
    Maths::GeoVector4<float> geo = *reinterpret_cast<Maths::GeoVector4<float>*>(gv);
    static Maths::GeoVector4<float> normal = geo.getNormalised();
    return reinterpret_cast<GeoVector4F_t*>(&normal);
  }

  float GeoVector4F_getLength(GeoVector4F_t* gv) {
    Maths::GeoVector4<float> geo = *reinterpret_cast<Maths::GeoVector4<float>*>(gv);
    return geo.getLength();
  }

  float GeoVector4F_getMagnitude(GeoVector4F_t* gv) {
    return GeoVector4F_getLength(gv);
  }

  bool GeoVector4F_equal(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) == *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  bool GeoVector4F_notEqual(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) != *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  bool GeoVector4F_lessThan(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) < *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  bool GeoVector4F_lessThanOrEqualTo(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) <= *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  bool GeoVector4F_greaterThan(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) > * reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  bool GeoVector4F_greaterThanOrEqualTo(const GeoVector4F_t* first, const GeoVector4F_t* other) {
    return *reinterpret_cast<const Maths::GeoVector4<float>*>(first) >= *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
  }

  GeoVector4F_t* GeoVector4F_addVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first) + *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_subtractVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first) - *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_multiplyVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first) * *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_divideVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first) / *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_addFloat(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector) + value;
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_subtractFloat(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector) - value;
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_multiplyFloat(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector) * value;
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_divideFloat(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector) / value;
    return reinterpret_cast<GeoVector4F_t*>(&geo);
  }

  GeoVector4F_t* GeoVector4F_addIntoVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first);
    geo += *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    first = reinterpret_cast<GeoVector4F_t*>(&geo);
    return first;
  }

  GeoVector4F_t* GeoVector4F_subtractFromVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first);
    geo -= *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    first = reinterpret_cast<GeoVector4F_t*>(&geo);
    return first;
  }

  GeoVector4F_t* GeoVector4F_multiplyIntoVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first);
    geo *= *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    first = reinterpret_cast<GeoVector4F_t*>(&geo);
    return first;
  }

  GeoVector4F_t* GeoVector4F_divideIntoVector(GeoVector4F_t* first, const GeoVector4F_t* other) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(first);
    geo /= *reinterpret_cast<const Maths::GeoVector4<float>*>(other);
    first = reinterpret_cast<GeoVector4F_t*>(&geo);
    return first;
  }

  GeoVector4F_t* GeoVector4F_addFloatIntoVector(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector);
    geo += value;
    vector = reinterpret_cast<GeoVector4F_t*>(&geo);
    return vector;
  }

  GeoVector4F_t* GeoVector4F_subFloatFromVector(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector);
    geo -= value;
    vector = reinterpret_cast<GeoVector4F_t*>(&geo);
    return vector;
  }

  GeoVector4F_t* GeoVector4F_multiplyFloatIntoVector(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector);
    geo *= value;
    vector = reinterpret_cast<GeoVector4F_t*>(&geo);
    return vector;
  }

  GeoVector4F_t* GeoVector4F_divideFloatIntoVector(GeoVector4F_t* vector, float value) {
    static NovelRT::Maths::GeoVector4<float> geo = *reinterpret_cast<const Maths::GeoVector4<float>*>(vector);
    geo /= value;
    vector = reinterpret_cast<GeoVector4F_t*>(&geo);
    return vector;
  }

  GeoVector4F_t* GeoVector4F_multiplyFloatIntoVectorInverse(float lhs, GeoVector4F_t* rhs) {
    return GeoVector4F_multiplyFloat(rhs, lhs);
  }

#ifdef __cplusplus
}
#endif
