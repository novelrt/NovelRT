// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root for more information.

#ifndef Nrt_INTEROP_TIMING_TIMESTAMP_H
#define Nrt_INTEROP_TIMING_TIMESTAMP_H

#include "../NrtInteropUtils.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t NrtTimestamp;

NrtTimestamp Nrt_Timestamp_create(uint64_t ticks);

NrtBool Nrt_Timestamp_isNaN(NrtTimestamp timestamp);
double Nrt_Timestamp_getSecondsDouble(NrtTimestamp timestamp);
float Nrt_Timestamp_getSecondsFloat(NrtTimestamp timestamp);
NrtTimestamp Nrt_Timestamp_zero();
NrtTimestamp Nrt_Timestamp_fromSeconds(double seconds);
NrtResult Nrt_Timestamp_addTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult Nrt_Timestamp_subtractTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult Nrt_Timestamp_multiplyTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult Nrt_Timestamp_divideTimestamp(NrtTimestamp first, NrtTimestamp other, NrtTimestamp* output);
NrtResult Nrt_Timestamp_addAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult Nrt_Timestamp_subtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult Nrt_Timestamp_multiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtResult Nrt_Timestamp_divideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
NrtBool Nrt_Timestamp_lessThan(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool Nrt_Timestamp_lessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool Nrt_Timestamp_greaterThan(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool Nrt_Timestamp_greaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool Nrt_Timestamp_equal(NrtTimestamp lhs, NrtTimestamp rhs);
NrtBool Nrt_Timestamp_notEqual(NrtTimestamp lhs, NrtTimestamp rhs);

#ifdef __cplusplus
}
#endif

#endif // Nrt_INTEROP_TIMING_TIMESTAMP_H