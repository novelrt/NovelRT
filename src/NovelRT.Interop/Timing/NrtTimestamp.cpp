// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NrtInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Timing/NrtTimestamp.h"
#include "NovelRT.Interop/NrtInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

//TODO: NOTHING IN THIS CLASS WORKS
int32_t Nrt_Timestamp_isNaN(NrtTimestamp timestamp) {
  if (timestamp == nullptr) {
    return NOVELRT_TRUE;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  if(std::isnan(static_cast<double>(ts->ticks))) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_create(uint64_t ticks, NrtTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto stamp = new Timing::Timestamp(ticks);
  *outputTimestamp = reinterpret_cast<NrtTimestamp>(&stamp);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_getSecondsDouble(NrtTimestamp timestamp, double* output) {
  if (timestamp == nullptr || output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(timestamp)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  *output = ts->getSecondsDouble();
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_getSecondsFloat(NrtTimestamp timestamp, float* output) {
  if (timestamp == nullptr || output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(timestamp)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  *output = ts->getSecondsFloat();
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_zero(NrtTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto stamp = new Timing::Timestamp(0ULL);
  *outputTimestamp = reinterpret_cast<NrtTimestamp>(&stamp);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_fromSeconds(double seconds, NrtTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  auto stamp = new Timing::Timestamp(0);
  *stamp = Timing::Timestamp::fromSeconds(seconds);
  *outputTimestamp = reinterpret_cast<NrtTimestamp>(&stamp);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_addTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  Timing::Timestamp* result = new Timing::Timestamp(0); 
  *result = cFirst + cOther;
  *output = reinterpret_cast<NrtTimestamp>(result);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_subtractTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  Timing::Timestamp* result = new Timing::Timestamp(0);
  *result = cFirst - cOther;
  *output = reinterpret_cast<NrtTimestamp>(result);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_multiplyTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);
  Timing::Timestamp result = cFirst * cOther;
  *output = reinterpret_cast<NrtTimestamp&>(result);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_divideTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output) {
  if (output == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  if (other == 0) {
    Nrt_setErrMsgIsDivideByZeroInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp result = cFirst / cOther;
  *output = reinterpret_cast<NrtTimestamp&>(result);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_addAssignTimestamp(NrtTimestamp first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) += *reinterpret_cast<Timing::Timestamp*>(other);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_subtractAssignTimestamp(NrtTimestamp first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) -= *reinterpret_cast<Timing::Timestamp*>(other);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_multiplyAssignTimestamp(NrtTimestamp first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) *= *reinterpret_cast<Timing::Timestamp*>(other);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_divideAssignTimestamp(NrtTimestamp first, NrtTimestamp other) {
  if (first == nullptr) {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(first) || Nrt_Timestamp_isNaN(other)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (other == 0) {
    Nrt_setErrMsgIsDivideByZeroInternal();
    return NRT_FAILURE_UNKOWN;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) /= *reinterpret_cast<Timing::Timestamp*>(other);
  return NRT_SUCCESS;
}

int32_t Nrt_Timestamp_lessThan(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst < cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_lessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst <= cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_greaterThan(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst > cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_greaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst >= cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_equal(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst == cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t Nrt_Timestamp_notEqual(NrtTimestamp lhs, NrtTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    Nrt_setErrMsgIsNullptrInternal();
    return NRT_FAILURE_UNKOWN;
  }

  if (Nrt_Timestamp_isNaN(lhs) || Nrt_Timestamp_isNaN(rhs)) {
    Nrt_setErrMsgIsNaNInternal();
    return NRT_FAILURE_UNKOWN;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst != cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

#ifdef __cplusplus
}
#endif
