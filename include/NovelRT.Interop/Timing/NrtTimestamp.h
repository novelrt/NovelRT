// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#ifndef NOVELRT_INTEROP_TIMING_TIMESTAMP_H
#define NOVELRT_INTEROP_TIMING_TIMESTAMP_H

#include "../NrtTypedefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

    NrtTimestamp Nrt_Timestamp_Create(uint64_t ticks);

    NrtBool Nrt_Timestamp_IsNaN(NrtTimestamp timestamp);
    double Nrt_Timestamp_GetSecondsDouble(NrtTimestamp timestamp);
    float Nrt_Timestamp_GetSecondsFloat(NrtTimestamp timestamp);
    NrtTimestamp Nrt_Timestamp_Zero();
    NrtTimestamp Nrt_Timestamp_FromSeconds(double seconds);
    NrtTimestamp Nrt_Timestamp_AddTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_SubtractTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_MultiplyTimestamp(NrtTimestamp first, NrtTimestamp other);
    NrtTimestamp Nrt_Timestamp_DivideTimestamp(NrtTimestamp first, NrtTimestamp other);
    void Nrt_Timestamp_AddAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_SubtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_MultiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    void Nrt_Timestamp_DivideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other);
    NrtBool Nrt_Timestamp_LessThan(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_LessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_GreaterThan(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_GreaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_Equal(NrtTimestamp lhs, NrtTimestamp rhs);
    NrtBool Nrt_Timestamp_NotEqual(NrtTimestamp lhs, NrtTimestamp rhs);

#ifdef __cplusplus
}
#endif

#endif // NOVELRT_INTEROP_TIMING_TIMESTAMP_H
