// Copyright © Matt Jones and Contributors. Licensed under the MIT Licence (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector4F.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#ifdef __cplusplus
extern "C"
{
    using namespace NovelRT;
#endif

    NrtGeoVector4F Nrt_GeoVector4F_CreateFromGeoVector2F(NrtGeoVector2F vector)
    {
        return NrtGeoVector4F{vector.x, vector.y, 0, 0};
    }

    NrtGeoVector4F Nrt_GeoVector4F_CreateFromGeoVector3F(NrtGeoVector3F vector)
    {
        return NrtGeoVector4F{vector.x, vector.y, vector.z, 0};
    }

    NrtGeoVector4F Nrt_GeoVector4F_getNaN()
    {
        return NrtGeoVector4F{NAN, NAN, NAN, NAN};
    }

    NrtBool Nrt_GeoVector4F_IsNaN(NrtGeoVector4F vector)
    {
        if (std::isnan(vector.x) || std::isnan(vector.y) || std::isnan(vector.z) || std::isnan(vector.w))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector4F Nrt_GeoVector4F_Uniform(float value)
    {
        return NrtGeoVector4F{value, value, value, value};
    }

    NrtGeoVector4F Nrt_GeoVector4F_Zero()
    {
        return Nrt_GeoVector4F_Uniform(0.0f);
    }

    NrtGeoVector4F Nrt_GeoVector4F_One()
    {
        return Nrt_GeoVector4F_Uniform(1.0f);
    }

    void Nrt_GeoVector4F_RotateToAngleAroundPointDeg(NrtGeoVector4F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector3F point)
    {
        Maths::GeoVector3F cPoint = *reinterpret_cast<const Maths::GeoVector3F*>(&point);
        (*reinterpret_cast<Maths::GeoVector4F*>(vector)).RotateToAngleAroundPointDeg(angleRotationValue, cPoint);
    }

    void Nrt_GeoVector4F_RotateToAngleAroundPointRad(NrtGeoVector4F* vector,
                                                  float angleRotationValue,
                                                  NrtGeoVector3F point)
    {
        Maths::GeoVector3F cPoint = *reinterpret_cast<const Maths::GeoVector3F*>(&point);
        (*reinterpret_cast<Maths::GeoVector4F*>(vector)).RotateToAngleAroundPointRad(angleRotationValue, cPoint);
    }

    NrtBool Nrt_GeoVector4F_EpsilonEquals(NrtGeoVector4F vector, NrtGeoVector4F other, NrtGeoVector4F epsilonValue)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&other);
        Maths::GeoVector4F cEpsilonValue = *reinterpret_cast<const Maths::GeoVector4F*>(&epsilonValue);

        if (cVector.EpsilonEquals(cOther, cEpsilonValue))
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector4F Nrt_GeoVector4F_GetNormalised(NrtGeoVector4F vector)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        Maths::GeoVector4F normal = cVector.GetNormalised();
        return *reinterpret_cast<NrtGeoVector4F*>(&normal);
    }

    float Nrt_GeoVector4F_GetLength(NrtGeoVector4F vector)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        return cVector.GetLength();
    }

    float Nrt_GeoVector4F_GetMagnitude(NrtGeoVector4F vector)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        return cVector.GetMagnitude();
    }

    float Nrt_GeoVector4F_GetSquaredLength(NrtGeoVector4F vector)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        return cVector.GetSquaredLength();
    }

    float Nrt_GeoVector4F_GetSquaredMagnitude(NrtGeoVector4F vector)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&vector);
        return cVector.GetSquaredMagnitude();
    }

    float Nrt_GeoVector4F_Dot(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

        return cFirst.Dot(cOther);
    }

    float Nrt_GeoVector4F_Distance(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

        return cFirst.Distance(cOther);
    }

    float Nrt_GeoVector4F_SquaredDistance(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);

        return cFirst.SquaredDistance(cOther);
    }

    NrtBool Nrt_GeoVector4F_Equal(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst == cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector4F_NotEqual(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst != cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector4F_LessThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst < cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector4F_LessThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst <= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector4F_GreaterThan(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst > cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtBool Nrt_GeoVector4F_GreaterThanOrEqualTo(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        if (cFirst >= cOther)
        {
            return NRT_TRUE;
        }

        return NRT_FALSE;
    }

    NrtGeoVector4F Nrt_GeoVector4F_AddVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        Maths::GeoVector4F result = cFirst + cOther;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_SubtractVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        Maths::GeoVector4F result = cFirst - cOther;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_MultiplyVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        Maths::GeoVector4F result = cFirst * cOther;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_DivideVector(NrtGeoVector4F lhs, NrtGeoVector4F rhs)
    {
        Maths::GeoVector4F cFirst = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F cOther = *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
        Maths::GeoVector4F result = cFirst / cOther;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_AddFloat(NrtGeoVector4F lhs, float rhs)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F result = cVector + rhs;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_SubtractFloat(NrtGeoVector4F lhs, float rhs)
    {
        const Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F result = cVector - rhs;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_MultiplyFloat(NrtGeoVector4F lhs, float rhs)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F result = cVector * rhs;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    NrtGeoVector4F Nrt_GeoVector4F_DivideFloat(NrtGeoVector4F lhs, float rhs)
    {
        Maths::GeoVector4F cVector = *reinterpret_cast<const Maths::GeoVector4F*>(&lhs);
        Maths::GeoVector4F result = cVector / rhs;
        return *reinterpret_cast<NrtGeoVector4F*>(&result);
    }

    void Nrt_GeoVector4F_AddAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) += *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    }

    void Nrt_GeoVector4F_SubtractAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) -= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    }

    void Nrt_GeoVector4F_MultiplyAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) *= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    }

    void Nrt_GeoVector4F_DivideAssignVector(NrtGeoVector4F* lhs, NrtGeoVector4F rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) /= *reinterpret_cast<const Maths::GeoVector4F*>(&rhs);
    }

    void Nrt_GeoVector4F_AddAssignFloat(NrtGeoVector4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) += rhs;
    }

    void Nrt_GeoVector4F_SubtractAssignFloat(NrtGeoVector4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) -= rhs;
    }

    void Nrt_GeoVector4F_MultiplyAssignFloat(NrtGeoVector4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) *= rhs;
    }

    void Nrt_GeoVector4F_DivideAssignFloat(NrtGeoVector4F* lhs, float rhs)
    {
        *reinterpret_cast<Maths::GeoVector4F*>(lhs) /= rhs;
    }

#ifdef __cplusplus
}
#endif
