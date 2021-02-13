// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoBounds.h>
#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.h>

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT;
#endif

    NrtGeoBounds Nrt_GeoBounds_zero()
    {
        return NrtGeoBounds{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};
    }

    NrtGeoVector2F Nrt_GeoBounds_getCornerInLocalSpace(NrtGeoBounds bounds, int32_t index)
    {
        Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
        Maths::GeoVector2F corner = cBounds.getCornerInLocalSpace(index);
        return reinterpret_cast<NrtGeoVector2F&>(corner);
    }

    NrtGeoVector2F Nrt_GeoBounds_getCornerInWorldSpace(NrtGeoBounds bounds, int32_t index)
    {
        Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
        Maths::GeoVector2F corner = cBounds.getCornerInWorldSpace(index);
        return reinterpret_cast<NrtGeoVector2F&>(corner);
    }

    NrtBool Nrt_GeoBounds_pointIsWithinBounds(NrtGeoBounds bounds, NrtGeoVector2F point)
    {
        Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
        Maths::GeoVector2F cPoint = *reinterpret_cast<Maths::GeoVector2F*>(&point);

        if (cBounds.pointIsWithinBounds(cPoint))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoBounds_getExtents(NrtGeoBounds bounds)
    {
        const Maths::GeoBounds cBounds = *reinterpret_cast<const Maths::GeoBounds*>(&bounds);
        Maths::GeoVector2F extents = cBounds.getExtents();
        return reinterpret_cast<NrtGeoVector2F&>(extents);
    }

    NrtResult Nrt_GeoBounds_intersectsWith(NrtGeoBounds first, NrtGeoBounds other, NrtBool* outputResult)
    {
        if (outputResult == nullptr)
        {
            Nrt_setErrMsgIsNullptrInternal();
            return NRT_FAILURE_NULLPTR_PROVIDED;
        }

        Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&first);
        Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&other);

        try
        {
            if (cFirst.intersectsWith(cOther))
            {
                *outputResult = NRT_TRUE;
            }
            else
            {
                *outputResult = NRT_FALSE;
            }

            return NRT_SUCCESS;
        }
        catch (const Exceptions::NotSupportedException)
        {
            Nrt_setErrMsgIsNotSupportedInternal();
            return NRT_FAILURE_NOT_SUPPORTED;
        }
    }

    NrtBool Nrt_GeoBounds_equal(NrtGeoBounds lhs, NrtGeoBounds rhs)
    {
        Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&lhs);
        Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&rhs);

        if (cFirst == cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoBounds_notEqual(NrtGeoBounds lhs, NrtGeoBounds rhs)
    {
        Maths::GeoBounds cFirst = *reinterpret_cast<const Maths::GeoBounds*>(&lhs);
        Maths::GeoBounds cOther = *reinterpret_cast<const Maths::GeoBounds*>(&rhs);

        if (cFirst != cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }
}
