// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/GeoVector3F_t.h"


#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  GeoVector3F_t GeoVector3F_create(float x, float y, float z) {
    return GeoVector3F_t{ x, y, z };
  }
  
  GeoVector3F_t GeoVector3F_createFromGeoVector2F(const GeoVector2F_t& vector) {
  	Maths::GeoVector2<float> cVector2 = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
  	return GeoVector3F_t{ cVector2.getX(), cVector2.getY(), 0.0f };
  }
  
  GeoVector3F_t GeoVector3F_uniform(float value) {
    return GeoVector3F_create(value, value, value);
  }
  
  GeoVector3F_t GeoVector3F_zero() {
    return GeoVector3F_uniform(0.0f);
  }
  
  GeoVector3F_t GeoVector3F_one() {
    return GeoVector3F_uniform(1.0f);
  }
  
  float GeoVector3F_getX(GeoVector3F_t& gv) {
    return gv.x;
  }
  
  void GeoVector3F_setX(GeoVector3F_t& gv, float value) {
    gv.x = value;
  }
  
  float GeoVector3F_getY(GeoVector3F_t& gv) {
    return gv.y;
  }
  
  void GeoVector3F_setY(GeoVector3F_t& gv, float value) {
    gv.y = value;
  }
  
  float GeoVector3F_getZ(GeoVector3F_t& gv) {
    return gv.z;
  }
  
  void GeoVector3F_setZ(GeoVector3F_t& gv, float value) {
    gv.z = value;
  }

  void GeoVector3F_rotateToAngleAroundPoint(GeoVector3F_t& vector, float angleRotationValue, const GeoVector3F_t& point) noexcept {
    Maths::GeoVector3<float>& cVector = reinterpret_cast<Maths::GeoVector3<float>&>(vector);
    const Maths::GeoVector3<float>& cPoint = reinterpret_cast<const Maths::GeoVector3<float>&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);
  }

  bool GeoVector3F_epsilonEquals(const GeoVector3F_t& vector, const GeoVector3F_t& other, const GeoVector3F_t& epsilonValue) noexcept {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    const Maths::GeoVector3<float>& cEpsilonValue = reinterpret_cast<const Maths::GeoVector3<float>&>(epsilonValue);
    return cVector.epsilonEquals(cOther, cEpsilonValue);
  }

  GeoVector3F_t GeoVector3F_getNormalised(const GeoVector3F_t& vector) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    Maths::GeoVector3<float> normal = cVector.getNormalised();
    return reinterpret_cast<GeoVector3F_t&>(normal);
  }

  float GeoVector3F_getLength(const GeoVector3F_t& vector) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    return cVector.getLength();
  }

  float GeoVector3F_getMagnitude(const GeoVector3F_t& vector) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    return cVector.getMagnitude();
  }

  bool GeoVector3F_equal(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst == cOther;
  }

  bool GeoVector3F_notEqual(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst != cOther;
  }

  bool GeoVector3F_lessThan(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst < cOther;
  }

  bool GeoVector3F_lessThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst <= cOther;
  }

  bool GeoVector3F_greaterThan(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst > cOther;
  }

  bool GeoVector3F_greaterThanOrEqualTo(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    return cFirst >= cOther;
  }

  GeoVector3F_t GeoVector3F_addVector(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    Maths::GeoVector3<float> result = cFirst + cOther;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_subtractVector(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    Maths::GeoVector3<float> result = cFirst - cOther;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_multiplyVector(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    Maths::GeoVector3<float> result = cFirst * cOther;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_divideVector(const GeoVector3F_t& first, const GeoVector3F_t& other) {
    const Maths::GeoVector3<float>& cFirst = reinterpret_cast<const Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    Maths::GeoVector3<float> result = cFirst / cOther;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_addFloat(const GeoVector3F_t& vector, float value) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    Maths::GeoVector3<float> result = cVector + value;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_subtractFloat(const GeoVector3F_t& vector, float value) {
    const Maths::GeoVector3<float> cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    Maths::GeoVector3<float> result = cVector - value;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_multiplyFloat(const GeoVector3F_t& vector, float value) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    Maths::GeoVector3<float> result = cVector * value;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  GeoVector3F_t GeoVector3F_divideFloat(const GeoVector3F_t& vector, float value) {
    const Maths::GeoVector3<float>& cVector = reinterpret_cast<const Maths::GeoVector3<float>&>(vector);
    Maths::GeoVector3<float> result = cVector / value;
    return reinterpret_cast<GeoVector3F_t&>(result);
  }

  void GeoVector3F_addIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
    Maths::GeoVector3<float>& cFirst = reinterpret_cast<Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    cFirst += cOther;
  }

  void GeoVector3F_subtractFromVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
    Maths::GeoVector3<float>& cFirst = reinterpret_cast<Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    cFirst -= cOther;
  }

  void GeoVector3F_multiplyIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
    Maths::GeoVector3<float>& cFirst = reinterpret_cast<Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    cFirst *= cOther;
  }

  void GeoVector3F_divideIntoVector(GeoVector3F_t& first, const GeoVector3F_t& other) {
    Maths::GeoVector3<float>& cFirst = reinterpret_cast<Maths::GeoVector3<float>&>(first);
    const Maths::GeoVector3<float>& cOther = reinterpret_cast<const Maths::GeoVector3<float>&>(other);
    cFirst /= cOther;
  }

  void GeoVector3F_addFloatIntoVector(GeoVector3F_t& vector, float value) {
    Maths::GeoVector3<float>& cVector = reinterpret_cast<Maths::GeoVector3<float>&>(vector);
    cVector += value;
  }

  void GeoVector3F_subFloatFromVector(GeoVector3F_t& vector, float value) {
    Maths::GeoVector3<float>& cVector = reinterpret_cast<Maths::GeoVector3<float>&>(vector);
    cVector -= value;
  }

  void GeoVector3F_multiplyFloatIntoVector(GeoVector3F_t& vector, float value) {
    Maths::GeoVector3<float>& cVector = reinterpret_cast<Maths::GeoVector3<float>&>(vector);
    cVector *= value;
  }

  void GeoVector3F_divideFloatIntoVector(GeoVector3F_t& vector, float value) {
    Maths::GeoVector3<float>& cVector = reinterpret_cast<Maths::GeoVector3<float>&>(vector);
    cVector /= value;
  }

  GeoVector3F_t GeoVector3F_multiplyFloatInverse(float lhs, const GeoVector3F_t& rhs) {
    return GeoVector3F_multiplyFloat(rhs, lhs);
  }

#ifdef __cplusplus
}
#endif

