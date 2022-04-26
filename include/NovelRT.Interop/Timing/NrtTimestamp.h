// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#define NOVELRT_INTEROP_TIMING_TIMESTAMP_H

#include <NovelRT.Interop/NrtTypedefs.h>

#ifdef __cplusplus
extern "C"
{
#endif

    NrtTimestamp Nrt_Timestamp_create(uint64_t ticks);

    NrtBool Nrt_Timestamp_isNaN(NrtTimestamp timestamp);
    double Nrt_Timestamp_getSecondsDouble(NrtTimestamp timestamp);
    float Nrt_Timestamp_getSecondsFloat(NrtTimestamp timestamp);
    NrtTimestamp Nrt_Timestamp_zero();
    NrtTimestamp Nrt_Timestamp_fromSeconds(double seconds);
    NrtTimestamp Nrt_Timestamp_addTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_subtractTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_multiplyTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_divideTimestamp(NrtTimestamp first, NrtTimestamp other);
    void Nrt_Timestamp_addAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_subtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_multiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_divideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    NrtBool Nrt_Timestamp_lessThan(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_lessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_greaterThan(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_greaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_equal(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_notEqual(NrtTimestamp lhs, NrtTimestamp rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_TIMESTAMP_H
