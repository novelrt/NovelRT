// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTGeoVector4F.h"

#ifdef __cplusplus
extern "C" {
  using namespace NovelRT;
#endif

  NovelRTGeoVector4F NovelRT_GeoVector4F_createFromGeoVector2F(NovelRTGeoVector2F vector) {
    return NovelRTGeoVector4F{ vector.x, vector.y, 0, 0 };
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_createFromGeoVector3F(NovelRTGeoVector3F vector) {
    return NovelRTGeoVector4F{ vector.x, vector.y, vector.z, 0 };
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_getNaN() {
    return NovelRTGeoVector4F{NAN, NAN, NAN, NAN};
  }

  NovelRTBool NovelRT_GeoVector4F_isNaN(NovelRTGeoVector4F vector) {
    if(std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z) || std::isnan(vector.w)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_uniform(float value) {
    return NovelRTGeoVector4F{ value, value, value, value };
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_zero() {
    return NovelRT_GeoVector4F_uniform(0.0f);
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_one() {
    return NovelRT_GeoVector4F_uniform(1.0f);
  }

  NovelRTResult NovelRT_GeoVector4F_rotateToAngleAroundPoint(NovelRTGeoVector4F* const vector, float angleRotationValue, NovelRTGeoVector3F point, const char** errorMessage) {
    if(vector == nullptr) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*vector) || NovelRT_GeoVector4F_isNaN(point)) {
      if(errorMessage != nullptr) {
      *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(*vector);
    const Maths::GeoVector3<float>& cPoint = reinterpret_cast<const Maths::GeoVector3<float>&>(point);
    cVector.rotateToAngleAroundPoint(angleRotationValue, cPoint);

    return NOVELRT_SUCCESS;
  }

  NovelRTBool NovelRT_GeoVector4F_epsilonEquals(NovelRTGeoVector4F vector, NovelRTGeoVector4F other, NovelRTGeoVector4F epsilonValue) {
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector); const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(other);
    const Maths::GeoVector4<float>& cEpsilonValue = reinterpret_cast<const Maths::GeoVector4<float>&>(epsilonValue);
    
    if(cVector.epsilonEquals(cOther, cEpsilonValue)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTGeoVector4F NovelRT_GeoVector4F_getNormalised(NovelRTGeoVector4F vector) {
    if(NovelRT_GeoVector4F_isNaN(vector)) {
      return NovelRT_GeoVector4F_getNaN();
    }
    
    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    Maths::GeoVector4<float> normal = cVector.getNormalised();
    return reinterpret_cast<NovelRTGeoVector4F&>(normal);
  }

  float NovelRT_GeoVector4F_getLength(NovelRTGeoVector4F vector) {
    if(NovelRT_GeoVector4F_isNaN(vector) ) {
      return NAN;
    }

    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    return cVector.getLength();
  }

  float NovelRT_GeoVector4F_getMagnitude(NovelRTGeoVector4F vector) {
    if(NovelRT_GeoVector4F_isNaN(vector) ) {
      return NAN;
    } 

    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(vector);
    return cVector.getMagnitude();
  }

  NovelRTBool NovelRT_GeoVector4F_equal(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst == cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector4F_notEqual(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst != cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector4F_lessThan(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst < cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector4F_lessThanOrEqualTo(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst <= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector4F_greaterThan(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst > cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTBool NovelRT_GeoVector4F_greaterThanOrEqualTo(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs) {
    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    if(cFirst >= cOther) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NovelRTResult NovelRT_GeoVector4F_addVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs) || NovelRT_GeoVector4F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    
    Maths::GeoVector4<float> result = cFirst + cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_subtractVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs) || NovelRT_GeoVector4F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    Maths::GeoVector4<float> result = cFirst - cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_multiplyVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs) || NovelRT_GeoVector4F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    Maths::GeoVector4<float> result = cFirst * cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS; 
  }

  NovelRTResult NovelRT_GeoVector4F_divideVector(NovelRTGeoVector4F lhs, NovelRTGeoVector4F rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }
      
      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs) || NovelRT_GeoVector4F_isNaN(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_equal(lhs, NovelRT_GeoVector4F_zero())  || NovelRT_GeoVector4F_equal(rhs, NovelRT_GeoVector4F_zero()) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cFirst = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    Maths::GeoVector4<float> result = cFirst / cOther;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_addFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    Maths::GeoVector4<float> result = cVector + rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_subtractFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float> cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    Maths::GeoVector4<float> result = cVector - rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_multiplyFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    Maths::GeoVector4<float> result = cVector * rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_divideFloat(NovelRTGeoVector4F lhs, float rhs, NovelRTGeoVector4F* const outputResult, const char** errorMessage) {
    if(outputResult == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(lhs)  || std::isnan(rhs)) {
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

    const Maths::GeoVector4<float>& cVector = reinterpret_cast<const Maths::GeoVector4<float>&>(lhs);
    Maths::GeoVector4<float> result = cVector / rhs;
    *outputResult = reinterpret_cast<NovelRTGeoVector4F&>(result);

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_addAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || NovelRT_GeoVector4F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    cFirst += cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_subtractAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || NovelRT_GeoVector4F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    cFirst -= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_multiplyAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || NovelRT_GeoVector4F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    cFirst *= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_divideAssignVector(NovelRTGeoVector4F* const lhs, NovelRTGeoVector4F rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || NovelRT_GeoVector4F_isNaN(rhs) ) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_equal(NovelRT_GeoVector4F_zero(), rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsDivideByZero();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cFirst = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    const Maths::GeoVector4<float>& cOther = reinterpret_cast<const Maths::GeoVector4<float>&>(rhs);
    cFirst /= cOther;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_addAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    cVector += rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_subtractAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    cVector -= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_multiplyAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNaN();
      }

      return NOVELRT_FAILURE;
    }

    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(rhs);
    cVector *= rhs;

    return NOVELRT_SUCCESS;
  }

  NovelRTResult NovelRT_GeoVector4F_divideAssignFloat(NovelRTGeoVector4F* const lhs, float rhs, const char** errorMessage) {
    if(lhs == nullptr) {
      if(errorMessage != nullptr) {
        *errorMessage = NovelRT_getErrMsgIsNullptr();
      }

      return NOVELRT_FAILURE;
    }

    if(NovelRT_GeoVector4F_isNaN(*lhs)  || std::isnan(rhs)) {
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

    Maths::GeoVector4<float>& cVector = reinterpret_cast<Maths::GeoVector4<float>&>(*lhs);
    cVector /= rhs;

    return NOVELRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
