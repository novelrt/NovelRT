// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT.h>
#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector2F vec2One = Nrt_GeoVector2F_uniform(0.0);
NrtGeoVector2F vec2Two = Nrt_GeoVector2F_uniform(0.0f);
NrtGeoVector2F vec2Three = Nrt_GeoVector2F_uniform(1.0f);

TEST(InteropGeoVector2Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_notEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_lessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_lessThanOrEqualTo(vec2One, vec2Three));
    EXPECT_TRUE(Nrt_GeoVector2F_lessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_greaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2One));
    EXPECT_TRUE(Nrt_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, staticZeroCallReturnsGeoVector2Zero)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, staticOneCallReturnsGeoVector2One)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    NrtGeoVector2F result = Nrt_GeoVector2F_addVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    NrtGeoVector2F result = Nrt_GeoVector2F_subtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_multiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_divideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), result));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    NrtGeoVector2F result = Nrt_GeoVector2F_addFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    NrtGeoVector2F result = Nrt_GeoVector2F_subtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_multiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(4.0f);
    NrtGeoVector2F result = Nrt_GeoVector2F_divideFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    Nrt_GeoVector2F_addAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    Nrt_GeoVector2F_subtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    Nrt_GeoVector2F_multiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    Nrt_GeoVector2F_divideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    Nrt_GeoVector2F_addAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_one();
    Nrt_GeoVector2F_subtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    Nrt_GeoVector2F_multiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector2F test = Nrt_GeoVector2F_uniform(2.0f);
    Nrt_GeoVector2F_divideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_getMagnitude(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength)
{
    NrtGeoVector2F cVector = Nrt_GeoVector2F_one();
    NrtGeoVector2F normal = Nrt_GeoVector2F_getNormalised(cVector);
    GeoVector2F& vec = *reinterpret_cast<GeoVector2F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector2F_getLength(normal), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    NrtGeoVector2F vec{0.0f, 1.0f};
    NrtGeoVector2F zero = Nrt_GeoVector2F_zero();
    Nrt_GeoVector2F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
    NrtGeoVector2F other{-1.0f, 0.0f};
    NrtGeoVector2F epsilon = Nrt_GeoVector2F_uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector2F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector2Test, isNaNReturnsTrueNaNVector)
{
    NrtGeoVector2F nanVec{NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector2F_isNaN(nanVec));
}