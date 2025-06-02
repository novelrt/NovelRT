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

TEST(InteropGeoVector2Test, EqualityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, InequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_NotEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, LessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_LessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, LessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_LessThanOrEqualTo(vec2One, vec2Three));
    EXPECT_TRUE(Nrt_GeoVector2F_LessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, GreaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, GreaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThanOrEqualTo(vec2Three, vec2One));
    EXPECT_TRUE(Nrt_GeoVector2F_GreaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, StaticUniformCallReturnsGeoVector2WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, StaticZeroCallReturnsGeoVector2Zero)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), test));
}

TEST(InteropGeoVector2Test, StaticOneCallReturnsGeoVector2One)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), test));
}

TEST(InteropGeoVector2Test, AddOperatorAddsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_AddVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, SubtractOperatorSubtractsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_SubtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), result));
}

TEST(InteropGeoVector2Test, MultiplyOperatorMultipliesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_MultiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, DivideOperatorDividesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_DivideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), result));
}

TEST(InteropGeoVector2Test, AddOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_AddFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, SubtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    NrtGeoVector2F result = Nrt_GeoVector2F_SubtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), result));
}

TEST(InteropGeoVector2Test, MultiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_MultiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, DivideOperatorDividesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_DivideFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_AddAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_SubtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Zero(), test));
}

TEST(InteropGeoVector2Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_MultiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_DivideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_One(), test));
}

TEST(InteropGeoVector2Test, AddAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_AddAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_One();
    Nrt_GeoVector2F_SubtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_MultiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, DivideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_Uniform(2.0f);
    Nrt_GeoVector2F_DivideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, GetNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_GetNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, GetMagnitudeReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_GetNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, GetLengthReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_GetNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_GetNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_GetSquaredMagnitude(normal), powf(normal.x, 2) + powf(normal.y, 2));
}

TEST(InteropGeoVector2Test, GetSquaredLengthReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_One();
    NrtGeoVector2F normal = Nrt_GeoVector2F_GetNormalised(cVector);
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

TEST(InteropGeoVector2Test, IsNaNReturnsTrueNaNVector)
{
    NrtGeoVector2F nanVec{NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector2F_IsNaN(nanVec));
}
