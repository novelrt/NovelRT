// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector4F.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector4F vec4One = Nrt_GeoVector4F_Uniform(0.0);
NrtGeoVector4F vec4Two = Nrt_GeoVector4F_Uniform(0.0f);
NrtGeoVector4F vec4Three = Nrt_GeoVector4F_Uniform(1.0f);

TEST(InteropGeoVector4Test, createFromGeoVector2ReturnsGeoVector4WithCorrectAndVerbatimValues)
{
    NrtGeoVector4F vec = Nrt_GeoVector4F_CreateFromGeoVector2F(Nrt_GeoVector2F_Uniform(1.0f));
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(NrtGeoVector4F{1.0f, 1.0f, 0.0f, 0.0f}, vec));
}

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(vec4One, vec4Two));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_NotEqual(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_LessThan(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_LessThanOrEqualTo(vec4One, vec4Three));
    EXPECT_TRUE(Nrt_GeoVector4F_LessThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_GreaterThan(vec4Three, vec4One));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_GreaterThanOrEqualTo(vec4Three, vec4One));
    EXPECT_TRUE(Nrt_GeoVector4F_GreaterThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector4WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(1.0f), vec4Three));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector4Zero)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Zero(), test));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector4One)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_One(), test));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    NrtGeoVector4F result = Nrt_GeoVector4F_Zero() = Nrt_GeoVector4F_AddVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    NrtGeoVector4F result = Nrt_GeoVector4F_Zero() = Nrt_GeoVector4F_SubtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Zero(), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_Zero() = Nrt_GeoVector4F_MultiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(4.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_DivideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_One(), result));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    NrtGeoVector4F result = Nrt_GeoVector4F_AddFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    NrtGeoVector4F result = Nrt_GeoVector4F_SubtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Zero(), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_MultiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(4.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_DivideFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    Nrt_GeoVector4F_AddAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    Nrt_GeoVector4F_SubtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Zero(), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    Nrt_GeoVector4F_MultiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    Nrt_GeoVector4F_DivideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_One(), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    Nrt_GeoVector4F_AddAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_One();
    Nrt_GeoVector4F_SubtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    Nrt_GeoVector4F_MultiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_Uniform(2.0f);
    Nrt_GeoVector4F_DivideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_Equal(Nrt_GeoVector4F_Uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_One();
    NrtGeoVector4F normal = Nrt_GeoVector4F_GetNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_One();
    NrtGeoVector4F normal = Nrt_GeoVector4F_GetNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_GetMagnitude(normal),
                    sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_One();
    NrtGeoVector4F normal = Nrt_GeoVector4F_GetNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_GetLength(normal),
                    sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_One();
    NrtGeoVector4F normal = Nrt_GeoVector4F_GetNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_GetSquaredMagnitude(normal), powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2) + powf(normal.w, 2));
}

TEST(InteropGeoVector4Test, GetSquaredLengthReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_One();
    NrtGeoVector4F normal = Nrt_GeoVector4F_GetNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_GetSquaredLength(normal), powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2) + powf(normal.w, 2));
}

TEST(InteropGeoVector4Test, DotReturnsCorrectValue)
{
    NrtGeoVector4F zero = Nrt_GeoVector4F_Zero();
    NrtGeoVector4F one = Nrt_GeoVector4F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_Dot(zero, one), (zero.x * one.x) + (zero.y * one.y) + (zero.z * one.z) + (zero.w * one.w));
}

TEST(InteropGeoVector4Test, DistanceReturnsCorrectValue)
{
    NrtGeoVector4F zero = Nrt_GeoVector4F_Zero();
    NrtGeoVector4F one = Nrt_GeoVector4F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_Distance(zero, one), sqrtf(powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2) + powf(zero.z - one.z, 2) + powf(zero.z - one.z, 2)));
}

TEST(InteropGeoVector4Test, SquaredDistanceReturnsCorrectValue)
{
    NrtGeoVector4F zero = Nrt_GeoVector4F_Zero();
    NrtGeoVector4F one = Nrt_GeoVector4F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_SquaredDistance(zero, one), powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2) + powf(zero.z - one.z, 2) + powf(zero.z - one.z, 2));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointDegRotatesCorrectAmount)
{
    NrtGeoVector4F vec{0.0f, 1.0f, 0.0f, 0.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    Nrt_GeoVector4F_RotateToAngleAroundPointDeg(&vec, 90.0f, zero);
    NrtGeoVector4F other{-1.0f, 0.0f, 0.0f, 0.0f};
    NrtGeoVector4F epsilon = Nrt_GeoVector4F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector4F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRadRotatesCorrectAmount)
{
    NrtGeoVector4F vec{0.0f, 1.0f, 0.0f, 0.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    Nrt_GeoVector4F_RotateToAngleAroundPointRad(&vec, NovelRT::Maths::Utilities::Tau<float>() / 4, zero);
    NrtGeoVector4F other{-1.0f, 0.0f, 0.0f, 0.0f};
    NrtGeoVector4F epsilon = Nrt_GeoVector4F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector4F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector4Test, isNaNReturnsTrueNaNVector)
{
    NrtGeoVector4F nanVec{NAN, NAN, NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector4F_IsNaN(nanVec));
}
