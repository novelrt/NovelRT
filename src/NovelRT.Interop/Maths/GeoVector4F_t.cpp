// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRT.Interop/Maths/GeoVector4F_t.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoVector4F_t GeoVector4F_create(float x, float y, float z, float w) {
    return GeoVector4F_t{ x, y, z, w };
  }

  GeoVector4F_t GeoVector4F_createFromGeoVector2F(const NovelRTGeoVector2F& vector) {
    return GeoVector4F_t{ vector.x, vector.y, 0, 0 };
  }

  GeoVector4F_t GeoVector4F_createFromGeoVector3F(const NovelRTGeoVector3F& vector) {
    return GeoVector4F_t{ vector.x, vector.y, vector.z, 0 };
  }

  const GeoVector4F_t GeoVector4F_uniform(float value) {
    return GeoVector4F_create(value, value, value, value);
  }

  const GeoVector4F_t GeoVector4F_zero() {
    return GeoVector4F_uniform(0.0f);
  }

  const GeoVector4F_t GeoVector4F_one() {
    return GeoVector4F_uniform(1.0f);
  }

  float GeoVector4F_getX(GeoVector4F_t& gv) {
    return gv.x;
  }

  void GeoVector4F_setX(GeoVector4F_t& gv, float value) {
    gv.x = value;
  }

  float GeoVector4F_getY(GeoVector4F_t& gv) {
    return gv.y;
  }

  void GeoVector4F_setY(GeoVector4F_t& gv, float value) {
    gv.y = value;
  }

  float GeoVector4F_getZ(GeoVector4F_t& gv) {
    return gv.z;
  }

  void GeoVector4F_setZ(GeoVector4F_t& gv, float value) {
    gv.z = value;
  }

  float GeoVector4F_getW(GeoVector4F_t& gv) {
    return gv.w;
  }

  void GeoVector4F_setW(GeoVector4F_t& gv, float value) {
    gv.w = value;
  }

  void GeoVector4F_rotateToAngleAroundPoint(GeoVector4F_t& vector, float angleRotationValue, const NovelRTGeoVector3F& point) noexcept {
    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(vector);
    const Maths::GeoVector3<float>& cPoint = reinterpret_cast<const Maths::GeoVector3<float>&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);
  }

  bool GeoVector4F_epsilonEquals(const GeoVector4F_t& vector, const GeoVector4F_t& other, const GeoVector4F_t& epsilonValue) noexcept {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    const Maths::GeoVector4<float>& cEpsilonValue = reinterpret_cast<const Maths::GeoVector4<float>&>(epsilonValue);
    return cVector.epsilonEquals(cOther, cEpsilonValue);
  }

  GeoVector4F_t GeoVector4F_getNormalised(const GeoVector4F_t& vector) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> normal = cVector.getNormalised();
    return reinterpret_cast<GeoVector4F_t&>(normal);
  }

  float GeoVector4F_getLength(const GeoVector4F_t& vector) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    return cVector.getLength();
  }

  float GeoVector4F_getMagnitude(const GeoVector4F_t& vector) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    return cVector.getMagnitude();
  }

  bool GeoVector4F_equal(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst == cOther;
  }

  bool GeoVector4F_notEqual(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst != cOther;
  }

  bool GeoVector4F_lessThan(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst < cOther;
  }

  bool GeoVector4F_lessThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst <= cOther;
  }

  bool GeoVector4F_greaterThan(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst > cOther;
  }

  bool GeoVector4F_greaterThanOrEqualTo(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    return cFirst >= cOther;
  }

  GeoVector4F_t GeoVector4F_addVector(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    Maths::GeoVector4<float> result = cFirst + cOther;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_subtractVector(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    Maths::GeoVector4<float> result = cFirst - cOther;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_multiplyVector(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    Maths::GeoVector4<float> result = cFirst * cOther;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_divideVector(const GeoVector4F_t& first, const GeoVector4F_t& other) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    Maths::GeoVector4<float> result = cFirst / cOther;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_addFloat(const GeoVector4F_t& vector, float value) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> result = cVector + value;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_subtractFloat(const GeoVector4F_t& vector, float value) {
    const Maths::GeoVector4<float> cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> result = cVector - value;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_multiplyFloat(const GeoVector4F_t& vector, float value) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> result = cVector * value;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  GeoVector4F_t GeoVector4F_divideFloat(const GeoVector4F_t& vector, float value) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> result = cVector / value;
    return reinterpret_cast<GeoVector4F_t&>(result);
  }

  void GeoVector4F_addIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    cFirst += cOther;
  }

  void GeoVector4F_subtractFromVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    cFirst -= cOther;
  }

  void GeoVector4F_multiplyIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    cFirst *= cOther;
  }

  void GeoVector4F_divideIntoVector(GeoVector4F_t& first, const GeoVector4F_t& other) {
    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(first);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    cFirst /= cOther;
  }

  void GeoVector4F_addFloatIntoVector(GeoVector4F_t& vector, float value) {
    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(vector);
    cVector += value;
  }

  void GeoVector4F_subFloatFromVector(GeoVector4F_t& vector, float value) {
    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(vector);
    cVector -= value;
  }

  void GeoVector4F_multiplyFloatIntoVector(GeoVector4F_t& vector, float value) {
    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(vector);
    cVector *= value;
  }

  void GeoVector4F_divideFloatIntoVector(GeoVector4F_t& vector, float value) {
    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(vector);
    cVector /= value;
  }

  GeoVector4F_t GeoVector4F_multiplyFloatInverse(float lhs, const GeoVector4F_t& rhs) {
    return GeoVector4F_multiplyFloat(rhs, lhs);
  }

#ifdef __cplusplus
}
#endif
