// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Timing/NrtTimestamp.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

NrtBool Nrt_Timestamp_isNaN(NrtTimestamp timestamp) {
  Timing::Timestamp ts = Timing::Timestamp(timestamp);
  if(std::isnan(static_cast<double>(ts.ticks))) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtTimestamp Nrt_Timestamp_create(uint64_t ticks) {
  auto stamp = new Timing::Timestamp(ticks);
  return reinterpret_cast<NrtTimestamp&>(*stamp);
}

double Nrt_Timestamp_getSecondsDouble(NrtTimestamp timestamp) {
  if (Nrt_Timestamp_isNaN(timestamp)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp ts = Timing::Timestamp(timestamp);
  return ts.getSecondsDouble();
}

float Nrt_Timestamp_getSecondsFloat(NrtTimestamp timestamp) {
  if (Nrt_Timestamp_isNaN(timestamp)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp ts = Timing::Timestamp(timestamp);
  return ts.getSecondsFloat();
}

NrtTimestamp Nrt_Timestamp_zero() {
  auto stamp = new Timing::Timestamp(0ULL);
  return reinterpret_cast<NrtTimestamp&>(*stamp);
}

NrtTimestamp Nrt_Timestamp_fromSeconds(double seconds) {
  auto stamp = new Timing::Timestamp(0);
  *stamp = Timing::Timestamp::fromSeconds(seconds);
  return reinterpret_cast<NrtTimestamp&>(*stamp);
}

NrtResult Nrt_Timestamp_addTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(first);
  Timing::Timestamp cOther = Timing::Timestamp(other);

  Timing::Timestamp* result = new Timing::Timestamp(0); 
  *result = cFirst + cOther;
  *output = reinterpret_cast<NrtTimestamp&>(*result);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_subtractTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(first);
  Timing::Timestamp cOther = Timing::Timestamp(other);

  Timing::Timestamp* result = new Timing::Timestamp(0);
  *result = cFirst - cOther;
  *output = reinterpret_cast<NrtTimestamp&>(*result);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_multiplyTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(first);
  Timing::Timestamp cOther = Timing::Timestamp(other);
  Timing::Timestamp* result = new Timing::Timestamp(0);
  *result = cFirst * cOther;
  *output = reinterpret_cast<NrtTimestamp&>(*result);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_divideTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(first);
  Timing::Timestamp cOther = Timing::Timestamp(other);

  if (other == 0) {
    Nrt_setErrMsgIsDivideByZeroInternal();
    return NRT_FAILURE_DIVIDE_BY_ZERO;
  }

  Timing::Timestamp* result = new Timing::Timestamp(0);
  *result = cFirst / cOther;
  *output = reinterpret_cast<NrtTimestamp&>(*result);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_addAssignTimestamp(NrtTimestamp* first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
  
  if (Nrt_Timestamp_isNaN(*first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }
  
  reinterpret_cast<Timing::Timestamp&>(*first) += Timing::Timestamp(other);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_subtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
  
  if (Nrt_Timestamp_isNaN(*first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  reinterpret_cast<Timing::Timestamp&>(*first) -= Timing::Timestamp(other);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_multiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
  
  if (Nrt_Timestamp_isNaN(*first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  reinterpret_cast<Timing::Timestamp&>(*first) *= Timing::Timestamp(other);
  return NRT_SUCCESS;
}

NrtResult Nrt_Timestamp_divideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_NULLPTR_PROVIDED;
  }
  
  if (Nrt_Timestamp_isNaN(*first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  if (other == 0) {
    Nrt_setErrMsgIsDivideByZeroInternal();
    return NRT_FAILURE_DIVIDE_BY_ZERO;
  }

  reinterpret_cast<Timing::Timestamp&>(*first) /= Timing::Timestamp(other);
  return NRT_SUCCESS;
}

NrtBool Nrt_Timestamp_lessThan(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst < cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtBool Nrt_Timestamp_lessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst <= cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtBool Nrt_Timestamp_greaterThan(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst > cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtBool Nrt_Timestamp_greaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst >= cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtBool Nrt_Timestamp_equal(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst == cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

NrtBool Nrt_Timestamp_notEqual(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_NOT_A_NUMBER;
  }

  Timing::Timestamp cFirst = Timing::Timestamp(lhs);
  Timing::Timestamp cOther = Timing::Timestamp(rhs);
  if(cFirst != cOther) {
    return NRT_TRUE;
  }

  return NRT_FALSE;
}

#ifdef __cplusplus
}
#endif
