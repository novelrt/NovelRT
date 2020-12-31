// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT.Interop/NrtInteropErrorHandlingInternal.h>
#include <NovelRT.h>
#include <cmath>

#ifndef NAN
#error                                                                                                                 \
    "The NovelRT Engine C API requires a definition of NaN. Please configure NaN or use a version of C that has support.
#endif

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT;
#endif

    NrtGeoVector2F Nrt_GeoVector2F_getNaN()
    {
        return NrtGeoVector2F{NAN, NAN};
    }

    NrtBool Nrt_GeoVector2F_isNaN(NrtGeoVector2F vector)
    {
        if (std::isnan(vector.x) || std::isnan(vector.y))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_uniform(float value)
    {
        return NrtGeoVector2F{value, value};
    }

    NrtGeoVector2F Nrt_GeoVector2F_zero()
    {
        return Nrt_GeoVector2F_uniform(0.0f);
    }

    NrtGeoVector2F Nrt_GeoVector2F_one()
    {
        return Nrt_GeoVector2F_uniform(1.0f);
    }

    void Nrt_GeoVector2F_rotateToAngleAroundPoint(NrtGeoVector2F* vector, float angleRotationValue,
                                                  NrtGeoVector2F point)
    {
        Maths::GeoVector2F cPoint = *reinterpret_cast<const Maths::GeoVector2F*>(&point);
        (*reinterpret_cast<Maths::GeoVector2F*>(vector)).rotateToAngleAroundPoint(angleRotationValue, cPoint);
    }

    NrtBool Nrt_GeoVector2F_epsilonEquals(NrtGeoVector2F vector, NrtGeoVector2F other, NrtGeoVector2F epsilonValue)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&other);
        Maths::GeoVector2F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector2F*>(&epsilonValue);

        if (cVector.epsilonEquals(cOther, cEpsilonValue))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_getNormalised(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        Maths::GeoVector2F normal = cVector.getNormalised();
        return *reinterpret_cast<NrtGeoVector2F*>(&normal);
    }

    float Nrt_GeoVector2F_getLength(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.getLength();
    }

    float Nrt_GeoVector2F_getMagnitude(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.getMagnitude();
    }

    NrtBool Nrt_GeoVector2F_equal(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst == cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_notEqual(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst != cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_lessThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst < cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_lessThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst <= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_greaterThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst > cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_greaterThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst >= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_addVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst + cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_subtractVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst - cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_multiplyVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst * cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_divideVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst / cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_addFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector + rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_subtractFloat(NrtGeoVector2F lhs, float rhs)
    {
        const Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector - rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_multiplyFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector * rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_divideFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector / rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    void Nrt_GeoVector2F_addAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) += *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_subtractAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_multiplyAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_divideAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_addAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) += rhs;
    }

    void Nrt_GeoVector2F_subtractAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= rhs;
    }

    void Nrt_GeoVector2F_multiplyAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) *= rhs;
    }

    void Nrt_GeoVector2F_divideAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= rhs;
    }

#ifdef __cplusplus
}
#endif
