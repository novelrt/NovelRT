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

  NovelRTResult NovelRT_GeoVector2F_rotateToAngleAroundPoint(NovelRTGeoVector2F* const vector, float angleRotationValue, NovelRTGeoVector2F point, const char** errorMessage) {
    if(vector == nullptr) {
      if(errorMessage != nullptr) {
      *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(*vector);
    const Maths::GeoVector2<float>& cPoint = reinterpret_cast<const Maths::GeoVector2<float>&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NOVELRT_SUCCESS;
  }

  NovelRTBool NovelRT_GeoVector2F_epsilonEquals(NovelRTGeoVector2F vector, NovelRTGeoVector2F other, NovelRTGeoVector2F epsilonValue) {
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector); const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(other);
    const Maths::GeoVector2<float>& cEpsilonValue = reinterpret_cast<const Maths::GeoVector2<float>&>(epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector2F NovelRT_GeoVector2F_getNormalised(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) == NOVELRT_TRUE) {
      return NovelRT_GeoVector2F_getNaN();
    }
    
    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    Maths::GeoVector2<float> normal = cVector.getNormalised();
    return reinterpret_cast<NovelRTGeoVector2F&>(normal);
  }

  float NovelRT_GeoVector2F_getLength(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) == NOVELRT_TRUE) {
      return NAN;
    }

    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    return cVector.getLength();
  }

  float NovelRT_GeoVector2F_getMagnitude(NovelRTGeoVector2F vector) {
    if(NovelRT_GeoVector2F_isNaN(vector) == NOVELRT_TRUE) {
      return NAN;
    } 

    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(vector);
    return cVector.getMagnitude();
  }

  NovelRTBool NovelRT_GeoVector2F_equal(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_notEqual(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_lessThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_lessThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_greaterThan(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector2F_greaterThanOrEqualTo(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs) {
    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTResult NovelRT_GeoVector2F_addVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    
    Maths::GeoVector2<float> result = cFirst + cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    Maths::GeoVector2<float> result = cFirst - cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    Maths::GeoVector2<float> result = cFirst * cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS; 
  }

  NovelRTResult NovelRT_GeoVector2F_divideVector(NovelRTGeoVector2F lhs, NovelRTGeoVector2F rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) || NovelRT_GeoVector2F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(lhs, NovelRT_GeoVector2F_zero()) == NOVELRT_TRUE || NovelRT_GeoVector2F_equal(rhs, NovelRT_GeoVector2F_zero()) == NOVELRT_TRUE) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsDivideByZero;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cFirst = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    Maths::GeoVector2<float> result = cFirst / cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    Maths::GeoVector2<float> result = cVector + rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float> cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    Maths::GeoVector2<float> result = cVector - rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    Maths::GeoVector2<float> result = cVector * rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideFloat(NovelRTGeoVector2F lhs, float rhs, NovelRTGeoVector2F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsDivideByZero;
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector2<float>& cVector = reinterpret_cast<const Maths::GeoVector2<float>&>(lhs);
    Maths::GeoVector2<float> result = cVector / rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector2F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addAssignVector(NovelRTGeoVector2F* const lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || NovelRT_GeoVector2F_isNaN(rhs) == NOVELRT_TRUE) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    cFirst += cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractAssignVector(NovelRTGeoVector2F* const lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || NovelRT_GeoVector2F_isNaN(rhs) == NOVELRT_TRUE) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    cFirst -= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyAssignVector(NovelRTGeoVector2F* const lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || NovelRT_GeoVector2F_isNaN(rhs) == NOVELRT_TRUE) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    cFirst *= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideAssignVector(NovelRTGeoVector2F* const lhs, NovelRTGeoVector2F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || NovelRT_GeoVector2F_isNaN(rhs) == NOVELRT_TRUE) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsDivideByZero;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cFirst = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    const Maths::GeoVector2<float>& cOther = reinterpret_cast<const Maths::GeoVector2<float>&>(rhs);
    cFirst /= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_addAssignFloat(NovelRTGeoVector2F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    cVector += rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_subtractAssignFloat(NovelRTGeoVector2F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    cVector -= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_multiplyAssignFloat(NovelRTGeoVector2F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(rhs);
    cVector *= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector2F_divideAssignFloat(NovelRTGeoVector2F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNullptr;
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector2F_isNaN(*lhs) == NOVELRT_TRUE || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsNaN;
      }

      return NOVELRT_FAILURE;
    }

    if(rhs == 0.0f) {
      if(errorMessage != nullptr) {
        *errorMessage = errMsgIsDivideByZero;
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector2<float>& cVector = reinterpret_cast<Maths::GeoVector2<float>&>(*lhs);
    cVector /= rhs;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
