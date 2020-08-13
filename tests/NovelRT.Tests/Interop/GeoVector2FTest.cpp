// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTGeoVector2F.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

NovelRTGeoVector2F vec2One = NovelRT_GeoVector2F_uniform(0.0);
NovelRTGeoVector2F vec2Two = NovelRT_GeoVector2F_uniform(0.0f);
NovelRTGeoVector2F vec2Three = NovelRT_GeoVector2F_uniform(1.0f);

TEST(InteropGeoVector2Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(vec2One, vec2Two));
}

TEST(InteropGeoVector2Test, createReturnsCorrectGeoVector2) {
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRTGeoVector2F{1.0f, 1.0f}, GeoVector2F_create(1.0f, 1.0f)));
}

TEST(InteropGeoVector2Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_notEqual(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThan(vec2One, vec2Three));
}

TEST(InteropGeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThanOrEqualTo(vec2One, vec2Three));
  EXPECT_TRUE(NovelRT_GeoVector2F_lessThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThan(vec2Three, vec2One));
}

TEST(InteropGeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2One));
  EXPECT_TRUE(NovelRT_GeoVector2F_greaterThanOrEqualTo(vec2Three, vec2Three));
}

TEST(InteropGeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), vec2Three));
}

TEST(InteropGeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  NovelRTGeoVector2F test = GeoVector2F_create(0.0f, 0.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, staticOneCallReturnsGeoVector2One) {
  NovelRTGeoVector2F test = GeoVector2F_create(1.0f, 1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_one(), test));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_addVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_subtractVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_multiplyVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_divideVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), result));
}

TEST(InteropGeoVector2Test, addOperatorAddsCorrectlyForFloatType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_addFloat(test, 1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), result));
}

TEST(InteropGeoVector2Test, subtractOperatorSubtractsCorrectlyForFloatType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(0.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloatType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, multiplyOperatorMultipliesCorrectlyForFloatTypeInverse) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = GeoVector2F_multiplyFloatInverse(2.0f, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), result));
}

TEST(InteropGeoVector2Test, divideOperatorDividesCorrectlyForFloatType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRTGeoVector2F result = NovelRT_GeoVector2F_divideFloat(test, 2.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), result));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRT_GeoVector2F_addIntoVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRT_GeoVector2F_subtractFromVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_zero(), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRT_GeoVector2F_multiplyIntoVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRT_GeoVector2F_divideIntoVector(test, test);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  NovelRT_GeoVector2F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.0f), test));
}

TEST(InteropGeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_one();
  GeoVector2F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(0.0f), test));
}

TEST(InteropGeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRT_GeoVector2F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(4.0f), test));
}

TEST(InteropGeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  NovelRTGeoVector2F test = NovelRT_GeoVector2F_uniform(2.0f);
  NovelRT_GeoVector2F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(1.0f), test));
}

TEST(InteropGeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector2Test, getMagnitudeReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector2F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(InteropGeoVector2Test, getLengthReturnsCorrectLength) {
  NovelRTGeoVector2F cVector = NovelRT_GeoVector2F_one();
  NovelRTGeoVector2F normal = NovelRT_GeoVector2F_getNormalised(cVector);
  GeoVector2<float>& vec = reinterpret_cast<GeoVector2<float>&>(normal);
  EXPECT_FLOAT_EQ(NovelRT_GeoVector2F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(InteropGeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  NovelRTGeoVector2F vec = GeoVector2F_create(0.0f, 1.0f);
  NovelRTGeoVector2F zero = NovelRT_GeoVector2F_zero();
  NovelRT_GeoVector2F_rotateToAngleAroundPoint(vec, 90.0f, zero);
  NovelRTGeoVector2F other = GeoVector2F_create(-1.0f, 0.0f);
  NovelRTGeoVector2F epsilon = NovelRT_GeoVector2F_uniform(1e-7f);

  EXPECT_TRUE(NovelRT_GeoVector2F_epsilonEquals(vec, other, epsilon));
}
