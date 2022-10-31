// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector2F vec2One = Nrt_GeoVector2F_Uniform(0.0);
NrtGeoVector2F vec2Two = Nrt_GeoVector2F_Uniform(0.0f);
NrtGeoVector2F vec2Three = Nrt_GeoVector2F_Uniform(1.0f);

TEST(InteropGeoVector2Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_NotEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_LessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_LessThanOrEqualTo(vec2One, vec2Three));
    EXPECT_TRUE(Nrt_GeoVector2F_LessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThanOrEqualTo(vec2Three, vec2One));
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, staticZeroCallReturnsGeoVector2Zero)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), test));
}

TEST(InteropGeoVector2Test, staticOneCallReturnsGeoVector2One)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), test));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_AddVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_SubtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_MultiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_DivideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), result));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_AddFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_SubtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_MultiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_DivideFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_AddAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_SubtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_MultiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_DivideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_AddAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_SubtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_MultiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_DivideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetSquaredMagnitude(normal), powf(normal.x, 2) + powf(normal.y, 2));
}

TEST(InteropGeoVector2Test, GetSquaredLengthReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetSquaredLength(normal), powf(normal.x, 2) + powf(normal.y, 2));
}

TEST(InteropGeoVector2Test, DotReturnsCorrectValue)
{
    NrtGeoVector2F zero = Nrt_GeoVector2F_Zero();
    NrtGeoVector2F one = Nrt_GeoVector2F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_Dot(zero, one), (zero.x * one.x) + (zero.y * one.y));
}

TEST(InteropGeoVector2Test, DistanceReturnsCorrectValue)
{
    NrtGeoVector2F zero = Nrt_GeoVector2F_Zero();
    NrtGeoVector2F one = Nrt_GeoVector2F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_Distance(zero, one), sqrtf(powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2)));
}

TEST(InteropGeoVector2Test, SquaredDistanceReturnsCorrectValue)
{
    NrtGeoVector2F zero = Nrt_GeoVector2F_Zero();
    NrtGeoVector2F one = Nrt_GeoVector2F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_SquaredDistance(zero, one), powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2));
}

TEST(InteropGeoVector2Test, RotateToAngleAroundPointDegRotatesCorrectAmount)
{
    NrtGeoVector2F vec{0.0f, 1.0f};
    NrtGeoVector2F zero = Nrt_GeoVector2F_Zero();
    Nrt_GeoVector2F_RotateToAngleAroundPointDeg(&vec, 90.0f, zero);
    NrtGeoVector2F other{-1.0f, 0.0f};
    NrtGeoVector2F epsilon = Nrt_GeoVector2F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector2F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector2Test, RotateToAngleAroundPointRadRotatesCorrectAmount)
{
    NrtGeoVector2F vec{0.0f, 1.0f};
    NrtGeoVector2F zero = Nrt_GeoVector2F_Zero();
    Nrt_GeoVector2F_RotateToAngleAroundPointRad(&vec, Maths::Utilities::Tau<float>() / 4, zero);
    NrtGeoVector2F other{-1.0f, 0.0f};
    NrtGeoVector2F epsilon = Nrt_GeoVector2F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector2F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector2Test, isNaNReturnsTrueNaNVector)
{
    NrtGeoVector2F nanVec{NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector2F_IsNaN(nanVec));
}
