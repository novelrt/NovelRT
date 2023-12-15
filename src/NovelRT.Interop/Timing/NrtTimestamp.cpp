// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT.Interop/Timing/NrtTimestamp.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtBool Nrt_Timestamp_IsNaN(NrtTimestamp timestamp)
    {
        Timing::Timestamp ts = Timing::Timestamp(timestamp);
        if (std::isnan(static_cast<double>(ts.ticks)))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtTimestamp Nrt_Timestamp_Create(uint64_t ticks)
    {
        auto stamp = new Timing::Timestamp(ticks);
        return reinterpret_cast<NrtTimestamp&>(*stamp);
    }

    double Nrt_Timestamp_GetSecondsDouble(NrtTimestamp timestamp)
    {
        Timing::Timestamp ts = Timing::Timestamp(timestamp);
        return ts.getSecondsDouble();
    }

    float Nrt_Timestamp_GetSecondsFloat(NrtTimestamp timestamp)
    {
        Timing::Timestamp ts = Timing::Timestamp(timestamp);
        return ts.getSecondsFloat();
    }

    NrtTimestamp Nrt_Timestamp_Zero()
    {
        auto stamp = new Timing::Timestamp(0ULL);
        return reinterpret_cast<NrtTimestamp&>(*stamp);
    }

    NrtTimestamp Nrt_Timestamp_FromSeconds(double seconds)
    {
        auto stamp = new Timing::Timestamp(0);
        *stamp = Timing::Timestamp::fromSeconds(seconds);
        return reinterpret_cast<NrtTimestamp&>(*stamp);
    }

    NrtTimestamp Nrt_Timestamp_AddTimestamp(NrtTimestamp first, NrtTimestamp other)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(first);
        Timing::Timestamp cOther = Timing::Timestamp(other);

        Timing::Timestamp* result = new Timing::Timestamp(0);
        *result = cFirst + cOther;
        return reinterpret_cast<NrtTimestamp&>(*result);
    }

    NrtTimestamp Nrt_Timestamp_SubtractTimestamp(NrtTimestamp first, NrtTimestamp other)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(first);
        Timing::Timestamp cOther = Timing::Timestamp(other);

        Timing::Timestamp* result = new Timing::Timestamp(0);
        *result = cFirst - cOther;
        return reinterpret_cast<NrtTimestamp&>(*result);
    }

    NrtTimestamp Nrt_Timestamp_MultiplyTimestamp(NrtTimestamp first, NrtTimestamp other)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(first);
        Timing::Timestamp cOther = Timing::Timestamp(other);

        Timing::Timestamp* result = new Timing::Timestamp(0);
        *result = cFirst * cOther;
        return reinterpret_cast<NrtTimestamp&>(*result);
    }

    NrtTimestamp Nrt_Timestamp_DivideTimestamp(NrtTimestamp first, NrtTimestamp other)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(first);
        Timing::Timestamp cOther = Timing::Timestamp(other);

        Timing::Timestamp* result = new Timing::Timestamp(0);
        *result = cFirst / cOther;
        return reinterpret_cast<NrtTimestamp&>(*result);
    }

    void Nrt_Timestamp_AddAssignTimestamp(NrtTimestamp* first, NrtTimestamp other)
    {
        reinterpret_cast<Timing::Timestamp&>(*first) += Timing::Timestamp(other);
    }

    void Nrt_Timestamp_SubtractAssignTimestamp(NrtTimestamp* first, NrtTimestamp other)
    {
        reinterpret_cast<Timing::Timestamp&>(*first) -= Timing::Timestamp(other);
    }

    void Nrt_Timestamp_MultiplyAssignTimestamp(NrtTimestamp* first, NrtTimestamp other)
    {
        reinterpret_cast<Timing::Timestamp&>(*first) *= Timing::Timestamp(other);
    }

    void Nrt_Timestamp_DivideAssignTimestamp(NrtTimestamp* first, NrtTimestamp other)
    {
        reinterpret_cast<Timing::Timestamp&>(*first) /= Timing::Timestamp(other);
    }

    NrtBool Nrt_Timestamp_LessThan(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst < cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_Timestamp_LessThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst <= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_Timestamp_GreaterThan(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst > cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_Timestamp_GreaterThanOrEqualTo(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst >= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_Timestamp_Equal(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst == cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_Timestamp_NotEqual(NrtTimestamp lhs, NrtTimestamp rhs)
    {
        Timing::Timestamp cFirst = Timing::Timestamp(lhs);
        Timing::Timestamp cOther = Timing::Timestamp(rhs);
        if (cFirst != cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

#ifdef __cplusplus
}
#endif
