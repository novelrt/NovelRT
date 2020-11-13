// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NrtGeoVector3F.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif
  
  NrtGeoVector3F Nrt_GeoVector3F_createFromGeoVector2F(NrtGeoVector2F vector) {
  	Maths::GeoVector2F cVector2 = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
  	return NrtGeoVector3F{ cVector2.x, cVector2.y, 0.0f };
  }

  NrtGeoVector3F Nrt_GeoVector3F_getNaN() {
    return NrtGeoVector3F{NAN, NAN, NAN};
  }

  NrtBool Nrt_GeoVector3F_isNaN(NrtGeoVector3F vector) {
    if(std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z)) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtGeoVector3F Nrt_GeoVector3F_uniform(float value) {
    return NrtGeoVector3F{ value, value, value };
  }

  NrtGeoVector3F Nrt_GeoVector3F_zero() {
    return Nrt_GeoVector3F_uniform(0.0f);
  }

  NrtGeoVector3F Nrt_GeoVector3F_one() {
    return Nrt_GeoVector3F_uniform(1.0f);
  }

  void Nrt_GeoVector3F_rotateToAngleAroundPoint(NrtGeoVector3F* vector, float angleRotationValue, NrtGeoVector3F point) {
    Maths::GeoVector3F cPoint = *reinterpret_cast<const Maths::GeoVector3F*>(&point);
    (*reinterpret_cast<Maths::GeoVector3F*>(vector)).rotateToAngleAroundPoint(angleRotationValue, cPoint);
  }

  NrtBool Nrt_GeoVector3F_epsilonEquals(NrtGeoVector3F vector, NrtGeoVector3F other, NrtGeoVector3F epsilonValue) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector); Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&other);
    Maths::GeoVector3F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector3F*>(&epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtGeoVector3F Nrt_GeoVector3F_getNormalised(NrtGeoVector3F vector) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    Maths::GeoVector3F normal = cVector.getNormalised();
    return *reinterpret_cast<NrtGeoVector3F*>(&normal);
  }

  float Nrt_GeoVector3F_getLength(NrtGeoVector3F vector) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    return cVector.getLength();
  }

  float Nrt_GeoVector3F_getMagnitude(NrtGeoVector3F vector) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    return cVector.getMagnitude();
  }

  NrtBool Nrt_GeoVector3F_equal(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst == cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector3F_notEqual(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst != cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector3F_lessThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst < cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector3F_lessThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst <= cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector3F_greaterThan(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst > cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector3F_greaterThanOrEqualTo(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst >= cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtGeoVector3F Nrt_GeoVector3F_addVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst + cOther;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_subtractVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst - cOther;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_multiplyVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst * cOther;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_divideVector(NrtGeoVector3F lhs, NrtGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst / cOther;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);  
  }

  NrtGeoVector3F Nrt_GeoVector3F_addFloat(NrtGeoVector3F lhs, float rhs) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector + rhs;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_subtractFloat(NrtGeoVector3F lhs, float rhs) {
    const Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector - rhs;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_multiplyFloat(NrtGeoVector3F lhs, float rhs, NrtGeoVector3F* outputResult) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector * rhs;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  NrtGeoVector3F Nrt_GeoVector3F_divideFloat(NrtGeoVector3F lhs, float rhs) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector / rhs;
    return *reinterpret_cast<NrtGeoVector3F*>(&result);
  }

  void Nrt_GeoVector3F_addAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) += *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
  }

  void Nrt_GeoVector3F_subtractAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
  }

  void Nrt_GeoVector3F_multiplyAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
  }

  void Nrt_GeoVector3F_divideAssignVector(NrtGeoVector3F* lhs, NrtGeoVector3F rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
  }

  void Nrt_GeoVector3F_addAssignFloat(NrtGeoVector3F* lhs, float rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) += rhs;
  }

  void Nrt_GeoVector3F_subtractAssignFloat(NrtGeoVector3F* lhs, float rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) -= rhs;
  }

  void Nrt_GeoVector3F_multiplyAssignFloat(NrtGeoVector3F* lhs, float rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(&rhs) *= rhs;
  }

  void Nrt_GeoVector3F_divideAssignFloat(NrtGeoVector3F* lhs, float rhs) {
    *reinterpret_cast<Maths::GeoVector3F*>(lhs) /= rhs;
  }

#ifdef __cplusplus
}
#endif

