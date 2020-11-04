// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.h>
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NrtGeoVector4F.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector2F(NrtGeoVector2F vector) {
    return NrtGeoVector4F{ vector.x, vector.y, 0, 0 };
  }

  NrtGeoVector4F Nrt_GeoVector4F_createFromGeoVector3F(NrtGeoVector3F vector) {
    return NrtGeoVector4F{ vector.x, vector.y, vector.z, 0 };
  }

  NrtGeoVector4F Nrt_GeoVector4F_getNaN() {
    return NrtGeoVector4F{NAN, NAN, NAN, NAN};
  }

  NrtBool Nrt_GeoVector4F_isNaN(NrtGeoVector4F vector) {
    if(std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z) || std::isnan(vector.w)) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtGeoVector4F Nrt_GeoVector4F_uniform(float value) {
    return NrtGeoVector4F{ value, value, value, value };
  }

  NrtGeoVector4F Nrt_GeoVector4F_zero() {
    return Nrt_GeoVector4F_uniform(0.0f);
  }

  NrtGeoVector4F Nrt_GeoVector4F_one() {
    return Nrt_GeoVector4F_uniform(1.0f);
  }

  NrtResult Nrt_GeoVector4F_rotateToAngleAroundPoint(NrtGeoVector4F* vector, float angleRotationValue, NrtGeoVector3F point) {
    if(vector == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*vector) || Nrt_GeoVector3F_isNaN(point)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector3F cPoint = *reinterpret_cast<const Maths::GeoVector3F*>(&point);
    (*reinterpret_cast<Maths::GeoVector4F*>(vector)).rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NRT_SUCCESS;
  }

  NrtBool Nrt_GeoVector4F_epsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue) {
    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector); Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&other);
    Maths::GeoVector4F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector4F*>(&epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtGeoVector4F Nrt_GeoVector4F_getNormalised(NrtGeoVector4F vector) {
    if(Nrt_GeoVector4F_isNaN(vector)) {
      return Nrt_GeoVector4F_getNaN();
    }
    
    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
    Maths::GeoVector4F normal = cVector.getNormalised();
    return *reinterpret_cast<NrtGeoVector4F*>(&normal);
  }

  float Nrt_GeoVector4F_getLength(NrtGeoVector4F vector) {
    if(Nrt_GeoVector4F_isNaN(vector) ) {
      return NAN;
    }

    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
    return cVector.getLength();
  }

  float Nrt_GeoVector4F_getMagnitude(NrtGeoVector4F vector) {
    if(Nrt_GeoVector4F_isNaN(vector) ) {
      return NAN;
    } 

    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
    return cVector.getMagnitude();
  }

  NrtBool Nrt_GeoVector4F_equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst == cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector4F_notEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst != cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector4F_lessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst < cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector4F_lessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst <= cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector4F_greaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst > cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtBool Nrt_GeoVector4F_greaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs) {
    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    if(cFirst >= cOther) {
      return NRT_TRUE;
    }

    return NRT_FALSE;
  }

  NrtResult Nrt_GeoVector4F_addVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs) || Nrt_GeoVector4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    
    Maths::GeoVector4F result = cFirst + cOther;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_subtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs) || Nrt_GeoVector4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    Maths::GeoVector4F result = cFirst - cOther;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_multiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs) || Nrt_GeoVector4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    Maths::GeoVector4F result = cFirst * cOther;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS; 
  }

  NrtResult Nrt_GeoVector4F_divideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs) || Nrt_GeoVector4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_equal(rhs, Nrt_GeoVector4F_zero()) ) {
      Nrt_setErrMsgIsDivideByZeroInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    Maths::GeoVector4F result = cFirst / cOther;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_addFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F result = cVector + rhs;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_subtractFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    const Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F result = cVector - rhs;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_multiplyFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F result = cVector * rhs;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_divideFloat(NrtGeoVector4F lhs, float rhs, NrtGeoVector4F* outputResult) {
    if(outputResult == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(rhs == 0.0f) {
      Nrt_setErrMsgIsDivideByZeroInternal();
      return NRT_FAILURE_UNKOWN;
    }

    Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
    Maths::GeoVector4F result = cVector / rhs;
    *outputResult = reinterpret_cast<NrtGeoVector4F&>(result);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_addAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || Nrt_GeoVector4F_isNaN(rhs) ) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) += *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_subtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || Nrt_GeoVector4F_isNaN(rhs) ) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_multiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || Nrt_GeoVector4F_isNaN(rhs) ) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_divideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || Nrt_GeoVector4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), rhs)) {
      Nrt_setErrMsgIsDivideByZeroInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_addAssignFloat(NrtGeoVector4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) += rhs;

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_subtractAssignFloat(NrtGeoVector4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) -= rhs;

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_multiplyAssignFloat(NrtGeoVector4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) *= rhs;

    return NRT_SUCCESS;
  }

  NrtResult Nrt_GeoVector4F_divideAssignFloat(NrtGeoVector4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(rhs == 0.0f) {
      Nrt_setErrMsgIsDivideByZeroInternal();
      return NRT_FAILURE_UNKOWN;
    }

    *reinterpret_cast<Maths::GeoVector4F*>(lhs) /= rhs;

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
