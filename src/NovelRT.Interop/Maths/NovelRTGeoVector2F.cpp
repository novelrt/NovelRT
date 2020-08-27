// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.h"
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

  NovelRTBool NovelRT_GeoVector2F_isNaN(NovelRTGeoVector2F vector) {
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

  NovelRTResult NovelRT_GeoVector2F_rotateToAngleAroundPoint(NovelRTGeoVector2F* vector, float angleRotationValue, NovelRTGeoVector2F point, const char** errorMessage) {
    if(vector == nullptr) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*vector) || NovelRT_GeoVector2F_isNaN(point)) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cVector = reinterpret_cast<Maths::GeoVector2F&>(*vector);
    const Maths::GeoVector2F& cPoint = reinterpret_cast<const Maths::GeoVector2F&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NOVELRT_SUCCESS;
  }

  NovelRTBool NovelRT_GeoVector2F_epsilonEquals(NovelRTGeoVector2F vector, NovelRTGeoVector2F other, NovelRTGeoVector2F epsilonValue) {
    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(vector); 
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(other);
    const Maths::GeoVector2F& cEpsilonValue = reinterpret_cast<const Maths::GeoVector2F&>(epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_getNormalised(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) ) {
      return NovelRT_GeoVector2F_getNaN();
    }
    
    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(vector);
    Maths::GeoVector2F normal = cVector.getNormalised();
    return reinterpret_cast<NovelRTGeoVector2F&>(normal);
  }

  float NovelRT_GeoVector2F_getLength(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) ) {
      return NAN;
    }

    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(vector);
    return cVector.getLength();
  }

  float NovelRT_GeoVector2F_getMagnitude(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) ) {
      return NAN;
    } 

    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(vector);
    return cVector.getMagnitude();
  }

  NovelRTBool NovelRT_GeoVector2F_equal(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_notEqual(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_lessThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_lessThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_greaterThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_greaterThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTResult NovelRT_GeoVector2F_addVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    
    Maths::GeoVector2F result = cFirst + cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    Maths::GeoVector2F result = cFirst - cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    Maths::GeoVector2F result = cFirst * cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS; 
  }

  NovelRTResult NovelRT_GeoVector2F_divideVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(lhs, NovelRT_GeoVector2F_zero())  || NovelRT_GeoVector2F_equal(rhs, NovelRT_GeoVector2F_zero()) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cFirst = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    Maths::GeoVector2F result = cFirst / cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    Maths::GeoVector2F result = cVector + rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F cVector = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    Maths::GeoVector2F result = cVector - rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    Maths::GeoVector2F result = cVector * rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs)  || std::isnan(rhs)) {
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

    const Maths::GeoVector2F& cVector = reinterpret_cast<const Maths::GeoVector2F&>(lhs);
    Maths::GeoVector2F result = cVector / rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cFirst = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    cFirst += cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cFirst = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    cFirst -= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cFirst = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    cFirst *= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideAssignVector(NovelRTGeoVector2F* lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || NovelRT_GeoVector2F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cFirst = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    const Maths::GeoVector2F& cOther = reinterpret_cast<const Maths::GeoVector2F&>(rhs);
    cFirst /= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addAssignFloat(NovelRTGeoVector2F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cVector = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    cVector += rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractAssignFloat(NovelRTGeoVector2F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cVector = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    cVector -= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyAssignFloat(NovelRTGeoVector2F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2F& cVector = reinterpret_cast<Maths::GeoVector2F&>(rhs);
    cVector *= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideAssignFloat(NovelRTGeoVector2F* lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs)  || std::isnan(rhs)) {
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

    Maths::GeoVector2F& cVector = reinterpret_cast<Maths::GeoVector2F&>(*lhs);
    cVector /= rhs;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
