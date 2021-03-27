// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NrtGeoVector3F.h>

#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector3F vec3One = Nrt_GeoVector3F_uniform(0.0);
NrtGeoVector3F vec3Two = Nrt_GeoVector3F_uniform(0.0f);
NrtGeoVector3F vec3Three = Nrt_GeoVector3F_uniform(1.0f);

TEST(InteropGeoVector3Test, createFromGeoVector2ReturnsGeoVector3WithCorrectAndVerbatimValues)
{
    NrtGeoVector3F vec = Nrt_GeoVector3F_createFromGeoVector2F(Nrt_GeoVector2F_uniform(1.0f));
    EXPECT_TRUE(Nrt_GeoVector3F_equal(NrtGeoVector3F{1.0f, 1.0f, 0.0f}, vec));
}

TEST(InteropGeoVector3Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_equal(vec3One, vec3Two));
}

TEST(InteropGeoVector3Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_notEqual(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_lessThan(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_lessThanOrEqualTo(vec3One, vec3Three));
    EXPECT_TRUE(Nrt_GeoVector3F_lessThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_greaterThan(vec3Three, vec3One));
}

TEST(InteropGeoVector3Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3One));
    EXPECT_TRUE(Nrt_GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, staticUniformCallReturnsGeoVector3WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(1.0f), vec3Three));
}

TEST(InteropGeoVector3Test, staticZeroCallReturnsGeoVector3Zero)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, staticOneCallReturnsGeoVector3One)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    NrtGeoVector3F result = Nrt_GeoVector3F_addVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    NrtGeoVector3F result = Nrt_GeoVector3F_zero() = Nrt_GeoVector3F_subtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_zero() = Nrt_GeoVector3F_multiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(4.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_zero() = Nrt_GeoVector3F_divideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), result));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    NrtGeoVector3F result = Nrt_GeoVector3F_zero() = Nrt_GeoVector3F_addFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    NrtGeoVector3F result = Nrt_GeoVector3F_subtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    NrtGeoVector3F result = Nrt_GeoVector3F_multiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    Nrt_GeoVector3F_addAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    Nrt_GeoVector3F_subtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    Nrt_GeoVector3F_multiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    Nrt_GeoVector3F_divideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    Nrt_GeoVector3F_addAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_one();
    Nrt_GeoVector3F_subtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    Nrt_GeoVector3F_multiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector3F test = Nrt_GeoVector3F_uniform(2.0f);
    Nrt_GeoVector3F_divideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector3F_equal(Nrt_GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, getNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
    NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector3Test, getMagnitudeReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
    NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_getMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, getLengthReturnsCorrectLength)
{
    NrtGeoVector3F cVector = Nrt_GeoVector3F_one();
    NrtGeoVector3F normal = Nrt_GeoVector3F_getNormalised(cVector);
    GeoVector3F& vec = *reinterpret_cast<GeoVector3F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector3F_getLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    NrtGeoVector3F vec{0.0f, 1.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_zero();
    Nrt_GeoVector3F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
    NrtGeoVector3F other{-1.0f, 0.0f};
    NrtGeoVector3F epsilon = Nrt_GeoVector3F_uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector3F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector3Test, isNaNReturnsTrueNaNVector)
{
    NrtGeoVector3F nanVec{NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector3F_isNaN(nanVec));
}
