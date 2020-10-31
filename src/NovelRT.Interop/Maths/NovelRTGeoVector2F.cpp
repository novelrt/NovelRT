// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"
#include <cmath>


#ifndef NAN
#error "The NovelRT Engine C API requires a definition of NaN. Please configure NaN or use a version of C that has support.
#endif

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  NovelRTGeoVector2F NovelRT_GeoVector2F_getNaN() {
    return NovelRTGeoVector2F{NAN, NAN};
  }

  int32_t NovelRT_GeoVector2F_isNaN(NovelRTGeoVector2F vector) {
    if(std::isnan(vector.x) || std::isnan(vector.y)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_uniform(float value) {
    return NovelRTGeoVector2F{ value, value };
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_zero() {
    return NovelRT_GeoVector2F_uniform(0.0f);
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_one() {
    return NovelRT_GeoVector2F_uniform(1.0f);
  }

  int32_t NovelRT_GeoVector2F_rotateToAngleAroundPoint(NovelRTGeoVector2F* vector, float angleRotationValue, NovelRTGeoVector2F point) {
    if(vector == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*vector) || NovelRT_GeoVector2F_isNaN(point)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cPoint = *reinterpret_cast<const Maths::GeoVector2F*>(&point);
    (*reinterpret_cast<Maths::GeoVector2F*>(vector)).rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_epsilonEquals(NovelRTGeoVector2F vector, NovelRTGeoVector2F other, NovelRTGeoVector2F epsilonValue) {
    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector); 
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&other);
    Maths::GeoVector2F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector2F*>(&epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_getNormalised(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector)) {
      return NovelRT_GeoVector2F_getNaN();
    }
    
    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
    Maths::GeoVector2F normal = cVector.getNormalised();
    return *reinterpret_cast<NovelRTGeoVector2F*>(&normal);
  }

  float NovelRT_GeoVector2F_getLength(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector)) {
      return NAN;
    }

    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
    return cVector.getLength();
  }

  float NovelRT_GeoVector2F_getMagnitude(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector)) {
      return NAN;
    } 

    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
    return cVector.getMagnitude();
  }

  int32_t NovelRT_GeoVector2F_equal(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_notEqual(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_lessThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_lessThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_greaterThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_greaterThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector2F_addVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    
    Maths::GeoVector2F result = cFirst + cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_subtractVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    Maths::GeoVector2F result = cFirst - cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_multiplyVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    Maths::GeoVector2F result = cFirst * cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS; 
  }

  int32_t NovelRT_GeoVector2F_divideVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(rhs, NovelRT_GeoVector2F_zero())) {
      NovelRT_setErrMsgIsDivideByZeroInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    Maths::GeoVector2F result = cFirst / cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_addFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F result = cVector + rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_subtractFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F result = cVector - rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_multiplyFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F result = cVector * rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_divideFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult) {
    if(outputResult == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      NovelRT_setErrMsgIsDivideByZeroInternal();
      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
    Maths::GeoVector2F result = cVector / rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_addAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }
    
    *reinterpret_cast<Maths::GeoVector2F*>(lhs) += *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_subtractAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_multiplyAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_divideAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), rhs)) {
      NovelRT_setErrMsgIsDivideByZeroInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_addAssignFloat(NovelRTGeoVector2F* lhs, float rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) += rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_subtractAssignFloat(NovelRTGeoVector2F* lhs, float rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_multiplyAssignFloat(NovelRTGeoVector2F* lhs, float rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(&rhs) *= rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector2F_divideAssignFloat(NovelRTGeoVector2F* lhs, float rhs) {
    if(lhs == nullptr) {
      NovelRT_setErrMsgIsNullptrInternal();
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      NovelRT_setErrMsgIsNaNInternal();
      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      NovelRT_setErrMsgIsDivideByZeroInternal();
      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= rhs;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
