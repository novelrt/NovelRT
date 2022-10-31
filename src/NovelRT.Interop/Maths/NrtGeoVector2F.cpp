// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#include <cmath>

#ifndef NAN
#error                                                                                                                 \
    The NovelRT Engine C API requires a definition of NaN. Please configure NaN or use a version of C that has support.
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

    NrtBool Nrt_GeoVector2F_IsNaN(NrtGeoVector2F vector)
    {
        if (std::isnan(vector.x) || std::isnan(vector.y))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_Uniform(float value)
    {
        return NrtGeoVector2F{value, value};
    }

    NrtGeoVector2F Nrt_GeoVector2F_Zero()
    {
        return Nrt_GeoVector2F_Uniform(0.0f);
    }

    NrtGeoVector2F Nrt_GeoVector2F_One()
    {
        return Nrt_GeoVector2F_Uniform(1.0f);
    }

    void Nrt_GeoVector2F_RotateToAngleAroundPointDeg(NrtGeoVector2F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector2F point)
    {
        Maths::GeoVector2F cPoint = *reinterpret_cast<const Maths::GeoVector2F*>(&point);
        (*reinterpret_cast<Maths::GeoVector2F*>(vector)).RotateToAngleAroundPointDeg(angleRotationValue, cPoint);
    }

    void Nrt_GeoVector2F_RotateToAngleAroundPointRad(NrtGeoVector2F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector2F point)
    {
        Maths::GeoVector2F cPoint = *reinterpret_cast<const Maths::GeoVector2F*>(&point);
        (*reinterpret_cast<Maths::GeoVector2F*>(vector)).RotateToAngleAroundPointRad(angleRotationValue, cPoint);
    }

    NrtBool Nrt_GeoVector2F_EpsilonEquals(NrtGeoVector2F vector, NrtGeoVector2F other, NrtGeoVector2F epsilonValue)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&other);
        Maths::GeoVector2F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector2F*>(&epsilonValue);

        if (cVector.EpsilonEquals(cOther, cEpsilonValue))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_getNormalised(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        Maths::GeoVector2F normal = cVector.GetNormalised();
        return *reinterpret_cast<NrtGeoVector2F*>(&normal);
    }

    float Nrt_GeoVector2F_GetLength(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.GetLength();
    }

    float Nrt_GeoVector2F_GetMagnitude(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.GetMagnitude();
    }

    float Nrt_GeoVector2F_GetSquaredLength(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.GetSquaredLength();
    }

    float Nrt_GeoVector2F_GetSquaredMagnitude(NrtGeoVector2F vector)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&vector);
        return cVector.GetSquaredMagnitude();
    }

    float Nrt_GeoVector2F_Dot(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

        return cFirst.Dot(cOther);
    }

    float Nrt_GeoVector2F_Distance(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

        return cFirst.Distance(cOther);
    }

    float Nrt_GeoVector2F_SquaredDistance(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);

        return cFirst.SquaredDistance(cOther);
    }

    NrtBool Nrt_GeoVector2F_Equal(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst == cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_NotEqual(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst != cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_LessThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst < cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_LessThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst <= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_GreaterThan(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst > cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector2F_GreaterThanOrEqualTo(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        if (cFirst >= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector2F Nrt_GeoVector2F_AddVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst + cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_SubtractVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst - cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_MultiplyVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst * cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_DivideVector(NrtGeoVector2F lhs, NrtGeoVector2F rhs)
    {
        Maths::GeoVector2F cFirst = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F cOther = *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
        Maths::GeoVector2F result = cFirst / cOther;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_AddFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector + rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_SubtractFloat(NrtGeoVector2F lhs, float rhs)
    {
        const Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector - rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_MultiplyFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector * rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    NrtGeoVector2F Nrt_GeoVector2F_DivideFloat(NrtGeoVector2F lhs, float rhs)
    {
        Maths::GeoVector2F cVector = *reinterpret_cast<const Maths::GeoVector2F*>(&lhs);
        Maths::GeoVector2F result = cVector / rhs;
        return *reinterpret_cast<NrtGeoVector2F*>(&result);
    }

    void Nrt_GeoVector2F_AddAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) += *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_SubtractAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_MultiplyAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_DivideAssignVector(NrtGeoVector2F* lhs, NrtGeoVector2F rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector2F*>(&rhs);
    }

    void Nrt_GeoVector2F_AddAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) += rhs;
    }

    void Nrt_GeoVector2F_SubtractAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) -= rhs;
    }

    void Nrt_GeoVector2F_MultiplyAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) *= rhs;
    }

    void Nrt_GeoVector2F_DivideAssignFloat(NrtGeoVector2F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector2F*>(lhs) /= rhs;
    }

#ifdef __cplusplus
}
#endif
