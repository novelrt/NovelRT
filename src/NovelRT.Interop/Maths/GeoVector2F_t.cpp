// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
#include "NovelRT.Interop/Maths/GeoVector2F_t.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  GeoVector2F_t GeoVector2F_create(float x, float y) {
     return GeoVector2F_t{ x, y };
  }

  GeoVector2F_t GeoVector2F_uniform(float value) {
    return GeoVector2F_t{ value, value };
  }

  GeoVector2F_t GeoVector2F_zero() {
    return GeoVector2F_uniform(0.0f);
  }

  GeoVector2F_t GeoVector2F_one() {
    return GeoVector2F_uniform(1.0f);
  }

  float GeoVector2F_getX(GeoVector2F_t& vector) {
    return vector.x;
  }

  void GeoVector2F_setX(GeoVector2F_t& vector, float value) {
    vector.x = value;
  }

  float GeoVector2F_getY(GeoVector2F_t& vector) {
    return vector.y;
  }

  void GeoVector2F_setY(GeoVector2F_t& vector, float value) {
    vector.y = value;
  }

  void GeoVector2F_rotateToAngleAroundPoint(GeoVector2F_t& vector, float angleRotationValue, const GeoVector2F_t& point) noexcept {
    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(vector);
    const Maths::GeoVector2<float>& cPoint = reinterpret_cast<const Maths::GeoVector2<float>&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);
  }

  bool GeoVector2F_epsilonEquals(const GeoVector2F_t& vector, const GeoVector2F_t& other, const GeoVector2F_t& epsilonValue) noexcept {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    const Maths::GeoVector2<float>& cEpsilonValue = reinterpret_cast<const Maths::GeoVector2<float>&>(epsilonValue);
    return cVector.epsilonEquals(cOther, cEpsilonValue);
  }

  GeoVector2F_t GeoVector2F_getNormalised(const GeoVector2F_t& vector) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> normal = cVector.getNormalised();
    return reinterpret_cast<GeoVector2F_t&>(normal);
  }

  float GeoVector2F_getLength(const GeoVector2F_t& vector) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    return cVector.getLength();
  }

  float GeoVector2F_getMagnitude(const GeoVector2F_t& vector) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    return cVector.getMagnitude();
  }

  bool GeoVector2F_equal(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst == cOther;
  }

  bool GeoVector2F_notEqual(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst != cOther;
  }

  bool GeoVector2F_lessThan(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst < cOther;
  }

  bool GeoVector2F_lessThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst <= cOther;
  }

  bool GeoVector2F_greaterThan(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst > cOther;
  }

  bool GeoVector2F_greaterThanOrEqualTo(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    return cFirst >= cOther;
  }

  GeoVector2F_t GeoVector2F_addVector(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    Maths::GeoVector2<float> result = cFirst + cOther;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_subtractVector(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    Maths::GeoVector2<float> result = cFirst - cOther;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_multiplyVector(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    Maths::GeoVector2<float> result = cFirst * cOther;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_divideVector(const GeoVector2F_t& first, const GeoVector2F_t& other) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    Maths::GeoVector2<float> result = cFirst / cOther;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_addFloat(const GeoVector2F_t& vector, float value) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> result = cVector + value;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_subtractFloat(const GeoVector2F_t& vector, float value) {
    const Maths::GeoVector2<float> cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> result = cVector - value;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_multiplyFloat(const GeoVector2F_t& vector, float value) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> result = cVector * value;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  GeoVector2F_t GeoVector2F_divideFloat(const GeoVector2F_t& vector, float value) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> result = cVector / value;
    return reinterpret_cast<GeoVector2F_t&>(result);
  }

  void GeoVector2F_addIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    cFirst += cOther;
  }

  void GeoVector2F_subtractFromVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    cFirst -= cOther;
  }

  void GeoVector2F_multiplyIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    cFirst *= cOther;
  }

  void GeoVector2F_divideIntoVector(GeoVector2F_t& first, const GeoVector2F_t& other) {
    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(first);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    cFirst /= cOther;
  }

  void GeoVector2F_addFloatIntoVector(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(vector);
    cVector += value;
  }

  void GeoVector2F_subFloatFromVector(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(vector);
    cVector -= value;
  }

  void GeoVector2F_multiplyFloatIntoVector(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(vector);
    cVector *= value;
  }

  void GeoVector2F_divideFloatIntoVector(GeoVector2F_t& vector, float value) {
    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(vector);
    cVector /= value;
  }

  GeoVector2F_t GeoVector2F_multiplyFloatInverse(float lhs, const GeoVector2F_t& rhs) {
    return GeoVector2F_multiplyFloat(rhs, lhs);
  }

#ifdef __cplusplus
}
#endif
