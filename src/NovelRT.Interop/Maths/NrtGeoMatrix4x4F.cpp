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

    NrtBool Nrt_GeoMatrix4x4F_isNaN(NrtGeoMatrix4x4F matrix)
    {
        if (Nrt_GeoVector4F_isNaN(matrix.x) || Nrt_GeoVector4F_isNaN(matrix.y) || Nrt_GeoVector4F_isNaN(matrix.z) ||
            Nrt_GeoVector4F_isNaN(matrix.w))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_getDefaultIdentity()
    {
        auto identity = Maths::GeoMatrix4x4F::getDefaultIdentity();
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&identity);
    }

    NrtBool Nrt_GeoMatrix4x4F_equal(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        if (*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) ==
            *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoMatrix4x4F_notEqual(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        if (*reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs) !=
            *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst + cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst - cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyMatrix(NrtGeoMatrix4x4F lhs, NrtGeoMatrix4x4F rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F cOther = *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst * cOther;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    void Nrt_GeoMatrix4x4F_addAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    void Nrt_GeoMatrix4x4F_subtractAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    void Nrt_GeoMatrix4x4F_multiplyAssignMatrix(NrtGeoMatrix4x4F* lhs, NrtGeoMatrix4x4F rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= *reinterpret_cast<const Maths::GeoMatrix4x4F*>(&rhs);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_addFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst + rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_subtractFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst - rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    NrtGeoMatrix4x4F Nrt_GeoMatrix4x4F_multiplyFloat(NrtGeoMatrix4x4F lhs, float rhs)
    {
        Maths::GeoMatrix4x4F cFirst = *reinterpret_cast<Maths::GeoMatrix4x4F*>(&lhs);
        Maths::GeoMatrix4x4F resultToReturn = cFirst * rhs;
        return *reinterpret_cast<NrtGeoMatrix4x4F*>(&resultToReturn);
    }

    void Nrt_GeoMatrix4x4F_addAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) += rhs;
    }

    void Nrt_GeoMatrix4x4F_subtractAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) -= rhs;
    }

    void Nrt_GeoMatrix4x4F_multiplyAssignFloat(NrtGeoMatrix4x4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoMatrix4x4F*>(lhs) *= rhs;
    }

#ifdef __cplusplus
}
#endif
