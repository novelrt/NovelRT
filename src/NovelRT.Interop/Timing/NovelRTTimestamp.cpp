// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#include "../NovelRTInteropErrorHandlingInternal.h"
#include "NovelRT.Interop/Timing/NovelRTTimestamp.h"
#include "NovelRT.Interop/NovelRTInteropUtils.h"
#include "NovelRT.h"

#ifdef __cplusplus
using namespace NovelRT;
extern "C" {
#endif

//TODO: NOTHING IN THIS CLASS WORKS
int32_t NovelRT_Timestamp_isNaN(NovelRTTimestamp timestamp) {
  if (timestamp == nullptr) {
    return NOVELRT_TRUE;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  if(std::isnan(static_cast<double>(ts->ticks))) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_create(uint64_t ticks, NovelRTTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto stamp = new Timing::Timestamp(ticks);
  *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_getSecondsDouble(NovelRTTimestamp timestamp, double* output) {
  if (timestamp == nullptr || output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(timestamp)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  *output = ts->getSecondsDouble();
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_getSecondsFloat(NovelRTTimestamp timestamp, float* output) {
  if (timestamp == nullptr || output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(timestamp)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp* ts = reinterpret_cast<Timing::Timestamp*>(timestamp);
  *output = ts->getSecondsFloat();
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_zero(NovelRTTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto stamp = new Timing::Timestamp(0ULL);
  *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_fromSeconds(double seconds, NovelRTTimestamp* outputTimestamp) {
  if (outputTimestamp == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  auto stamp = new Timing::Timestamp(0);
  *stamp = Timing::Timestamp::fromSeconds(seconds);
  *outputTimestamp = reinterpret_cast<NovelRTTimestamp>(&stamp);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_addTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output) {
  if (output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  Timing::Timestamp* result = new Timing::Timestamp(0); 
  *result = cFirst + cOther;
  *output = reinterpret_cast<NovelRTTimestamp>(result);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output) {
  if (output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  Timing::Timestamp* result = new Timing::Timestamp(0);
  *result = cFirst - cOther;
  *output = reinterpret_cast<NovelRTTimestamp>(result);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output) {
  if (output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);
  Timing::Timestamp result = cFirst * cOther;
  *output = reinterpret_cast<NovelRTTimestamp&>(result);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_divideTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output) {
  if (output == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(first);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(other);

  if (other == 0) {
    NovelRT_setErrMsgIsDivideByZeroInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp result = cFirst / cOther;
  *output = reinterpret_cast<NovelRTTimestamp&>(result);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_addAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other) {
  if (first == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) += *reinterpret_cast<Timing::Timestamp*>(other);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_subtractAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other) {
  if (first == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) -= *reinterpret_cast<Timing::Timestamp*>(other);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_multiplyAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other) {
  if (first == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) *= *reinterpret_cast<Timing::Timestamp*>(other);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_divideAssignTimestamp(NovelRTTimestamp first, NovelRTTimestamp other) {
  if (first == nullptr) {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(first) || NovelRT_Timestamp_isNaN(other)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  if (other == 0) {
    NovelRT_setErrMsgIsDivideByZeroInternal();
    return NOVELRT_FAILURE;
  }

  *reinterpret_cast<Timing::Timestamp*>(first) /= *reinterpret_cast<Timing::Timestamp*>(other);
  return NOVELRT_SUCCESS;
}

int32_t NovelRT_Timestamp_lessThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst < cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_lessThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst <= cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst > cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_greaterThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst >= cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_equal(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
  }

  Timing::Timestamp cFirst = *reinterpret_cast<Timing::Timestamp*>(lhs);
  Timing::Timestamp cOther = *reinterpret_cast<Timing::Timestamp*>(rhs);
  if(cFirst == cOther) {
    return NOVELRT_TRUE;
  }

  return NOVELRT_FALSE;
}

int32_t NovelRT_Timestamp_notEqual(NovelRTTimestamp lhs, NovelRTTimestamp rhs) {
  if (lhs == nullptr || rhs == nullptr)  {
    NovelRT_setErrMsgIsNullptrInternal();
    return NOVELRT_FAILURE;
  }

  if (NovelRT_Timestamp_isNaN(lhs) || NovelRT_Timestamp_isNaN(rhs)) {
    NovelRT_setErrMsgIsNaNInternal();
    return NOVELRT_FAILURE;
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
