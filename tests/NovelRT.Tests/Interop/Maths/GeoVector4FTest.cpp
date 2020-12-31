// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector4F.h>
#include <NovelRT.h>
#include <cmath>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

NrtGeoVector4F vec4One = Nrt_GeoVector4F_uniform(0.0);
NrtGeoVector4F vec4Two = Nrt_GeoVector4F_uniform(0.0f);
NrtGeoVector4F vec4Three = Nrt_GeoVector4F_uniform(1.0f);

TEST(InteropGeoVector4Test, createFromGeoVector2ReturnsGeoVector4WithCorrectAndVerbatimValues)
{
    NrtGeoVector4F vec = Nrt_GeoVector4F_createFromGeoVector2F(Nrt_GeoVector2F_uniform(1.0f));
    EXPECT_TRUE(Nrt_GeoVector4F_equal(NrtGeoVector4F{1.0f, 1.0f, 0.0f, 0.0f}, vec));
}

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_equal(vec4One, vec4Two));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_notEqual(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_lessThan(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_lessThanOrEqualTo(vec4One, vec4Three));
    EXPECT_TRUE(Nrt_GeoVector4F_lessThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_greaterThan(vec4Three, vec4One));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly)
{
    EXPECT_TRUE(Nrt_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4One));
    EXPECT_TRUE(Nrt_GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector4WithUniformValues)
{
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(1.0f), vec4Three));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector4Zero)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(0.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector4One)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    NrtGeoVector4F result = Nrt_GeoVector4F_zero() = Nrt_GeoVector4F_addVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    NrtGeoVector4F result = Nrt_GeoVector4F_zero() = Nrt_GeoVector4F_subtractVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_zero() = Nrt_GeoVector4F_multiplyVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_divideVector(test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), result));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    NrtGeoVector4F result = Nrt_GeoVector4F_addFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    NrtGeoVector4F result = Nrt_GeoVector4F_subtractFloat(test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_multiplyFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(4.0f);
    NrtGeoVector4F result = Nrt_GeoVector4F_divideFloat(test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    Nrt_GeoVector4F_addAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    Nrt_GeoVector4F_subtractAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    Nrt_GeoVector4F_multiplyAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    Nrt_GeoVector4F_divideAssignVector(&test, test);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    Nrt_GeoVector4F_addAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_one();
    Nrt_GeoVector4F_subtractAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    Nrt_GeoVector4F_multiplyAssignFloat(&test, 1.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForFloat)
{
    NrtGeoVector4F test = Nrt_GeoVector4F_uniform(2.0f);
    Nrt_GeoVector4F_divideAssignFloat(&test, 2.0f);
    EXPECT_TRUE(Nrt_GeoVector4F_equal(Nrt_GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
    NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
    EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
    NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_getMagnitude(normal),
                    sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength)
{
    NrtGeoVector4F cVector = Nrt_GeoVector4F_one();
    NrtGeoVector4F normal = Nrt_GeoVector4F_getNormalised(cVector);
    GeoVector4F& vec = *reinterpret_cast<GeoVector4F*>(&normal);
    EXPECT_FLOAT_EQ(Nrt_GeoVector4F_getLength(normal),
                    sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount)
{
    NrtGeoVector4F vec{0.0f, 1.0f};
    NrtGeoVector3F zero = Nrt_GeoVector3F_zero();
    Nrt_GeoVector4F_rotateToAngleAroundPoint(&vec, 90.0f, zero);
    NrtGeoVector4F other{-1.0f, 0.0f};
    NrtGeoVector4F epsilon = Nrt_GeoVector4F_uniform(1e-7f);
    EXPECT_TRUE(Nrt_GeoVector4F_epsilonEquals(vec, other, epsilon));
}

TEST(InteropGeoVector4Test, isNaNReturnsTrueNaNVector)
{
    NrtGeoVector4F nanVec{NAN, NAN};
    EXPECT_TRUE(Nrt_GeoVector4F_isNaN(nanVec));
}
