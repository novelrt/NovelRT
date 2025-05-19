// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoMatrix4x4F.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#include <cmath>

#ifdef __cplusplus
using namespace NovelRT;
extern "C"
{
#endif

    NrtBool Nrt_GeoMatrix4x4F_IsNaN(NrtGeoMatrix4x4F matrix)
    {
        if (Nrt_GeoVector4F_IsNaN(matrix.x) || Nrt_GeoVector4F_IsNaN(matrix.y) || Nrt_GeoVector4F_IsNaN(matrix.z) ||
            Nrt_GeoVector4F_IsNaN(matrix.w))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_GetDefaultIdentity()
    {
        auto identity = Maths::GeoMatrix4x4F::GetDefaultIdentity();
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&identity);
    }

    NrtBool Nrt_GeoMatrix4x4F_Equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        if (*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) ==
            *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoMatrix4x4F_NotEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        if (*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) !=
            *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_AddMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst + cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_SubtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst - cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_MultiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst * cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    void Nrt_GeoMatrix4x4F_AddAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    void Nrt_GeoMatrix4x4F_SubtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    void Nrt_GeoMatrix4x4F_MultiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_AddFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst + rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_SubtractFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst - rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_MultiplyFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst * rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    void Nrt_GeoMatrix4x4F_AddAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += rhs;
    }

    void Nrt_GeoMatrix4x4F_SubtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= rhs;
    }

    void Nrt_GeoMatrix4x4F_MultiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= rhs;
    }

#ifdef __cplusplus
}
#endif
