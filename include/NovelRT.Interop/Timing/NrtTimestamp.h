// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#define NOVELRT_INTEROP_TIMING_TIMESTAMP_H

#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t NrtTimestamp;

NrtTimestamp Nrt_Timestamp_create(uint64_t ticks);

NrtBool NovelRT_Timestamp_isNaN(NrtTimestamp timestamp);
double NovelRT_Timestamp_getSecondsDouble(NrtTimestamp timestamp);
float NovelRT_Timestamp_getSecondsFloat(NrtTimestamp timestamp);
NrtTimestamp NovelRT_Timestamp_zero();
NrtTimestamp NovelRT_Timestamp_fromSeconds(double seconds);
NrtResult NovelRT_Timestamp_addTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult NovelRT_Timestamp_subtractTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult NovelRT_Timestamp_multiplyTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult NovelRT_Timestamp_divideTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult NovelRT_Timestamp_addAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult NovelRT_Timestamp_subtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult NovelRT_Timestamp_multiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult NovelRT_Timestamp_divideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtBool NovelRT_Timestamp_lessThan(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool NovelRT_Timestamp_lessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool NovelRT_Timestamp_greaterThan(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool NovelRT_Timestamp_greaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool NovelRT_Timestamp_equal(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool NovelRT_Timestamp_notEqual(NrtTimestamp lhs, NrtTimestamp rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_TIMESTAMP_H