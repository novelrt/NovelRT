// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "NovelRT.h"
#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h"
#include <cmath>

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

  int32_t Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F matrix) {
    if(Nrt_GeoVector4F_isNaN(matrix.x) || Nrt_GeoVector4F_isNaN(matrix.y) || Nrt_GeoVector4F_isNaN(matrix.z) || Nrt_GeoVector4F_isNaN(matrix.w)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_getDefaultIdentity() {
    auto identity = Maths::GeoMatrix4x4F::getDefaultIdentity();
    return *reinterpret_cast<NrtGeoMatrix4x4F*>(&identity);
  }

  int32_t Nrt_GeoMatrix4x4F_equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs) {
    if(*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) == *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t Nrt_GeoMatrix4x4F_notEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs) {
    if(*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) != *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs)) {
      return NOVELRT_TRUE;
    }

    return NOVELRT_FALSE;
  }

  int32_t Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst + cOther;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst - cOther;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst * cOther;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_addAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_subtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_multiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || Nrt_GeoMatrix4x4F_isNaN(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F lhs, float rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst + rhs;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F lhs, float rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst - rhs;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F lhs, float rhs, NrtGeoMatrix4x4F* result) {
    if(result == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
    Maths::GeoMatrix4x4F resultToReturn = cFirst * rhs;
    *result = *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_addAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += rhs;

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_subtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= rhs;

    return NRT_SUCCESS;
  }

  int32_t Nrt_GeoMatrix4x4F_multiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs) {
    if(lhs == nullptr) {
      Nrt_setErrMsgIsNullptrInternal();
      return NRT_FAILURE_UNKOWN;
    }

    if(Nrt_GeoMatrix4x4F_isNaN(*lhs) || std::isnan(rhs)) {
      Nrt_setErrMsgIsNaNInternal();
      return NRT_FAILURE_UNKOWN;
    }
    
    *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= rhs;

    return NRT_SUCCESS;
  }

#ifdef __cplusplus
}
#endif
