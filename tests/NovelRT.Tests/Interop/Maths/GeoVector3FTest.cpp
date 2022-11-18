// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector3F.h>
#include <NovelRT/NovelRT.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector3F vec3One = Nrt_GeoVector3F_Uniform(0.0);
NrtGeoVector3F vec3Two = Nrt_GeoVector3F_Uniform(0.0f);
NrtGeoVector3F vec3Three = Nrt_GeoVector3F_Uniform(1.0f);

TEST(InteropGeoVector3Test, CreateFromGeoVector2ReturnsGeoVector3WithCorrectAndVerbatimValues)
{
    NrtGeoVector3F vec = Nrt_GeoVector3F_CreateFromGeoVector2F(Nrt_GeoVector2F_Uniform(1.0f));
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(NrtGeoVector3F{1.0f, 1.0f, 0.0f}, vec));
}

TEST(InteropGeoVector3Test, EqualityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(vec3One, vec3Two));
}

TEST(InteropGeoVector3Test, InequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_NotEqual(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, LessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_LessThan(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, LessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_LessThanOrEqualTo(vec3One, vec3Three));
    EXPECT_TRUE(Nrt_GeoVector3F_LessThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, GreaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_GreaterThan(vec3Three, vec3One));
}

TEST(InteropGeoVector3Test, GreaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_GreaterThanOrEqualTo(vec3Three, vec3One));
    EXPECT_TRUE(Nrt_GeoVector3F_GreaterThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, StaticUniformCallReturnsGeoVector3WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(1.0f), vec3Three));
}

TEST(InteropGeoVector3Test, StaticZeroCallReturnsGeoVector3Zero)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Zero(), test));
}

TEST(InteropGeoVector3Test, StaticOneCallReturnsGeoVector3One)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_One(), test));
}

TEST(InteropGeoVector3Test, AddOperatorAddsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    NrtGeoVector3F result = Nrt_GeoVector3F_AddVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, SubtractOperatorSubtractsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    NrtGeoVector3F result = Nrt_GeoVector3F_Zero() = Nrt_GeoVector3F_SubtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Zero(), result));
}

TEST(InteropGeoVector3Test, MultiplyOperatorMultipliesCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_Zero() = Nrt_GeoVector3F_MultiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, DivideOperatorDividesCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(4.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_Zero() = Nrt_GeoVector3F_DivideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_One(), result));
}

TEST(InteropGeoVector3Test, AddOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    NrtGeoVector3F result = Nrt_GeoVector3F_Zero() = Nrt_GeoVector3F_AddFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, SubtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    NrtGeoVector3F result = Nrt_GeoVector3F_SubtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Zero(), result));
}

TEST(InteropGeoVector3Test, MultiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_MultiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    Nrt_GeoVector3F_AddAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    Nrt_GeoVector3F_SubtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Zero(), test));
}

TEST(InteropGeoVector3Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    Nrt_GeoVector3F_MultiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    Nrt_GeoVector3F_DivideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_One(), test));
}

TEST(InteropGeoVector3Test, AddAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    Nrt_GeoVector3F_AddAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, SubtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_One();
    Nrt_GeoVector3F_SubtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    Nrt_GeoVector3F_MultiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, DivideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_Uniform(2.0f);
    Nrt_GeoVector3F_DivideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(Nrt_GeoVector3F_Uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, GetNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_One();
    NrtGeoVector3F normal = Nrt_GeoVector3F_GetNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector3Test, GetMagnitudeReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_One();
    NrtGeoVector3F normal = Nrt_GeoVector3F_GetNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_GetMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, GetLengthReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_One();
    NrtGeoVector3F normal = Nrt_GeoVector3F_GetNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_GetLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, GetSquaredMagnitudeReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_One();
    NrtGeoVector3F normal = Nrt_GeoVector3F_GetNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_GetSquaredMagnitude(normal),
                    powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2));
}

TEST(InteropGeoVector3Test, GetSquaredLengthReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_One();
    NrtGeoVector3F normal = Nrt_GeoVector3F_GetNormalised(cVector);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_GetSquaredLength(normal),
                    powf(normal.x, 2) + powf(normal.y, 2) + powf(normal.z, 2));
}

TEST(InteropGeoVector3Test, DotReturnsCorrectValue)
{
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    NrtGeoVector3F one = Nrt_GeoVector3F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_Dot(zero, one), (zero.x * one.x) + (zero.y * one.y) + (zero.z * one.z));
}

TEST(InteropGeoVector3Test, CrossReturnsCorrectValue)
{
    NrtGeoVector3F vecA{1.0f, 2.0f, 3.0f};
    NrtGeoVector3F vecB{4.0f, 5.0f, 6.0f};
    NrtGeoVector3F control{(vecA.y * vecB.z) - (vecA.z * vecB.y), (vecA.z * vecB.x) - (vecA.x * vecB.z),
                           (vecA.x * vecB.y) - (vecA.y * vecB.x)};
    NrtGeoVector3F crossProduct = Nrt_GeoVector3F_Cross(vecA, vecB);
    EXPECT_TRUE(Nrt_GeoVector3F_Equal(crossProduct, control));
}

TEST(InteropGeoVector3Test, DistanceReturnsCorrectValue)
{
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    NrtGeoVector3F one = Nrt_GeoVector3F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_Distance(zero, one),
                    sqrtf(powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2) + powf(zero.z - one.z, 2)));
}

TEST(InteropGeoVector3Test, SquaredDistanceReturnsCorrectValue)
{
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    NrtGeoVector3F one = Nrt_GeoVector3F_One();
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_SquaredDistance(zero, one),
                    powf(zero.x - one.x, 2) + powf(zero.y - one.y, 2) + powf(zero.z - one.z, 2));
}

TEST(InteropGeoVector3Test, RotateToAngleAroundPointDegRotatesCorrectAmount)
{
    NrtGeoVector3F vec{0.0f, 1.0f, 0.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    Nrt_GeoVector3F_RotateToAngleAroundPointDeg(&vec, 90.0f, zero);
    NrtGeoVector3F other{-1.0f, 0.0f, 0.0f};
    NrtGeoVector3F epsilon = Nrt_GeoVector3F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector3F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, RotateToAngleAroundPointRadRotatesCorrectAmount)
{
    NrtGeoVector3F vec{0.0f, 1.0f, 0.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_Zero();
    Nrt_GeoVector3F_RotateToAngleAroundPointRad(&vec, NovelRT::Maths::Utilities::Tau<float>() / 4, zero);
    NrtGeoVector3F other{-1.0f, 0.0f, 0.0f};
    NrtGeoVector3F epsilon = Nrt_GeoVector3F_Uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector3F_EpsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, IsNaNReturnsTrueNaNVector)
{
    NrtGeoVector3F nanVec{NAN, NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector3F_IsNaN(nanVec));
}
