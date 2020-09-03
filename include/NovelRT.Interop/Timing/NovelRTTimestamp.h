// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.
#include "NovelRT.Interop/NovelRTInteropUtils.h"

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#define NOVELRT_INTEROP_TIMING_TIMESTAMP_H

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t NovelRTTimestamp;

NovelRTTimestamp NovelRT_Timestamp_create(uint64_t ticks);

NovelRTBool NovelRT_Timestamp_isNaN(NovelRTTimestamp timestamp);
double NovelRT_Timestamp_getSecondsDouble(NovelRTTimestamp timestamp);
float NovelRT_Timestamp_getSecondsFloat(NovelRTTimestamp timestamp);
NovelRTTimestamp NovelRT_Timestamp_zero();
NovelRTTimestamp NovelRT_Timestamp_fromSeconds(double seconds);
NovelRTResult NovelRT_Timestamp_addTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_subtractTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_multiplyTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_divideTimestamp(NovelRTTimestamp first, NovelRTTimestamp other, NovelRTTimestamp* output, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_addAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_subtractAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_multiplyAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage);
NovelRTResult NovelRT_Timestamp_divideAssignTimestamp(NovelRTTimestamp* first, NovelRTTimestamp other, const char** errorMessage);
NovelRTBool NovelRT_Timestamp_lessThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs);
NovelRTBool NovelRT_Timestamp_lessThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs);
NovelRTBool NovelRT_Timestamp_greaterThan(NovelRTTimestamp lhs, NovelRTTimestamp rhs);
NovelRTBool NovelRT_Timestamp_greaterThanOrEqualTo(NovelRTTimestamp lhs, NovelRTTimestamp rhs);
NovelRTBool NovelRT_Timestamp_equal(NovelRTTimestamp lhs, NovelRTTimestamp rhs);
NovelRTBool NovelRT_Timestamp_notEqual(NovelRTTimestamp lhs, NovelRTTimestamp rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_TIMESTAMP_H