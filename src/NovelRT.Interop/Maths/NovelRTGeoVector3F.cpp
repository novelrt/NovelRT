// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTGeoVector3F.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif
  
  NovelRTGeoVector3F NovelRT_GeoVector3F_createFromGeoVector2F(NovelRTGeoVector2F vector) {
  	Maths::GeoVector2F cVector2 = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
  	return NovelRTGeoVector3F{ cVector2.x, cVector2.y, 0.0f };
  }

  NovelRTGeoVector3F NovelRT_GeoVector3F_getNaN() {
    return NovelRTGeoVector3F{NAN, NAN, NAN};
  }

  int32_t NovelRT_GeoVector3F_isNaN(NovelRTGeoVector3F vector) {
    if(std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector3F NovelRT_GeoVector3F_uniform(float value) {
    return NovelRTGeoVector3F{ value, value, value };
  }

  NovelRTGeoVector3F NovelRT_GeoVector3F_zero() {
    return NovelRT_GeoVector3F_uniform(0.0f);
  }

  NovelRTGeoVector3F NovelRT_GeoVector3F_one() {
    return NovelRT_GeoVector3F_uniform(1.0f);
  }

  int32_t NovelRT_GeoVector3F_rotateToAngleAroundPoint(NovelRTGeoVector3F* vector, float angleRotationValue, NovelRTGeoVector3F point, const char** errorMessage) {
    if(vector == nullptr) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*vector) || NovelRT_GeoVector3F_isNaN(point)) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cPoint = *reinterpret_cast<const Maths::GeoVector3F*>(&point);
    (*reinterpret_cast<Maths::GeoVector3F*>(vector)).rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_epsilonEquals(NovelRTGeoVector3F vector, NovelRTGeoVector3F other, NovelRTGeoVector3F epsilonValue) {
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector); Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&other);
    Maths::GeoVector3F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector3F*>(&epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector3F NovelRT_GeoVector3F_getNormalised(NovelRTGeoVector3F vector) {
    if(NovelRT_GeoVector3F_isNaN(vector)) {
      return NovelRT_GeoVector3F_getNaN();
    }
    
    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    Maths::GeoVector3F normal = cVector.getNormalised();
    return *reinterpret_cast<NovelRTGeoVector3F*>(&normal);
  }

  float NovelRT_GeoVector3F_getLength(NovelRTGeoVector3F vector) {
    if(NovelRT_GeoVector3F_isNaN(vector) ) {
      return NAN;
    }

    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    return cVector.getLength();
  }

  float NovelRT_GeoVector3F_getMagnitude(NovelRTGeoVector3F vector) {
    if(NovelRT_GeoVector3F_isNaN(vector) ) {
      return NAN;
    } 

    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&vector);
    return cVector.getMagnitude();
  }

  int32_t NovelRT_GeoVector3F_equal(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_notEqual(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_lessThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_lessThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_greaterThan(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_greaterThanOrEqualTo(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs) {
    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t NovelRT_GeoVector3F_addVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs) || NovelRT_GeoVector3F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    
    Maths::GeoVector3F result = cFirst + cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_subtractVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs) || NovelRT_GeoVector3F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst - cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_multiplyVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs) || NovelRT_GeoVector3F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst * cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS; 
  }

  int32_t NovelRT_GeoVector3F_divideVector(NovelRTGeoVector3F lhs, NovelRTGeoVector3F rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs) || NovelRT_GeoVector3F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_equal(lhs, NovelRT_GeoVector3F_zero())  || NovelRT_GeoVector3F_equal(rhs, NovelRT_GeoVector3F_zero()) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cFirst = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F cOther = *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);
    Maths::GeoVector3F result = cFirst / cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_addFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector + rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_subtractFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector - rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_multiplyFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector * rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_divideFloat(NovelRTGeoVector3F lhs, float rhs, NovelRTGeoVector3F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector3F cVector = *reinterpret_cast<const Maths::GeoVector3F*>(&lhs);
    Maths::GeoVector3F result = cVector / rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector3F&>(result);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_addAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || NovelRT_GeoVector3F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) += *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_subtractAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || NovelRT_GeoVector3F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_multiplyAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || NovelRT_GeoVector3F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_divideAssignVector(NovelRTGeoVector3F* lhs, NovelRTGeoVector3F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || NovelRT_GeoVector3F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_equal(NovelRT_GeoVector3F_zero(), rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector3F*>(&rhs);

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_addAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) += rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_subtractAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) -= rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_multiplyAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(&rhs) *= rhs;

    return NOVELRT_SUCCESS;
  }

  int32_t NovelRT_GeoVector3F_divideAssignFloat(NovelRTGeoVector3F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector3F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    *reinterpret_cast<Maths::GeoVector3F*>(lhs) /= rhs;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif

