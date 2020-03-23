// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelC/GeoVector2F.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

GeoVector2F_t one = { 0.0f, 0.0f };
GeoVector2F_t two = { 0.0f, 0.0f };
GeoVector2F_t three = { 1.0f, 1.0f };

TEST(C_GeoVector2F_Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_equal(one,two));
}

TEST(C_GeoVector2F_Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_notEqual(one, three));
}

TEST(C_GeoVector2F_Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_lessThan(one, three));
}

TEST(C_GeoVector2F_Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_lessThanOrEqualTo(one, three));
  EXPECT_TRUE(GeoVector2F_lessThanOrEqualTo(three, three));
}

TEST(C_GeoVector2F_Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_greaterThan(three, one));
}

TEST(C_GeoVector2F_Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_greaterThanOrEqualTo(three, one));
  EXPECT_TRUE(GeoVector2F_greaterThanOrEqualTo(three, three));
}

TEST(C_GeoVector2F_Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(1.0f), three));
}

TEST(C_GeoVector2F_Test, staticZeroCallReturnsGeoVector2Zero) {
  GeoVector2F_t test = GeoVector2F_create(0.0f, 0.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_zero(), test));
}

TEST(C_GeoVector2F_Test, staticOneCallReturnsGeoVector2One) {
  GeoVector2F_t test = GeoVector2F_create(1.0f, 1.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_one(), test));
}

TEST(C_GeoVector2F_Test, addOperatorAddsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_one();
  GeoVector2F_t result = GeoVector2F_addVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(2.0f), result));
}

TEST(C_GeoVector2F_Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_one();
  GeoVector2F_t result = GeoVector2F_subtractVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_zero(), result));
}

TEST(C_GeoVector2F_Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_uniform(2.0f);
  GeoVector2F_t result = GeoVector2F_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(4.0f), result));
}

TEST(C_GeoVector2F_Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_uniform(2.0f);
  GeoVector2F_t result = GeoVector2F_divideVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(1.0f), result));
}

TEST(C_GeoVector2F_Test, addOperatorAddsCorrectlyForFloatType) {
  GeoVector2F test = GeoVector2F_one();
  GeoVector2F result = GeoVector2F_addFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(2.0f), result));
}

TEST(C_GeoVector2F_Test, subtractOperatorSubtractsCorrectlyForFloatType) {
  GeoVector2F test = GeoVector2F_one();
  GeoVector2F result = GeoVector2F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(0.0f), result));
}

TEST(C_GeoVector2F_Test, multiplyOperatorMultipliesCorrectlyForFloatType) {
  GeoVector2F test = GeoVector2F_uniform(2.0f);
  GeoVector2F result = GeoVector2F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(4.0f), result));
}

TEST(C_GeoVector2F_Test, multiplyOperatorMultipliesCorrectlyForFloatTypeInverse) {
  GeoVector2F test = GeoVector2F_uniform(2.0f);
  GeoVector2F result = GeoVector2F_multiplyFloatIntoVectorInverse(2.0f, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(4.0f), result));
}

TEST(C_GeoVector2F_Test, divideOperatorDividesCorrectlyForFloatType) {
  GeoVector2F test = GeoVector2F_uniform(2.0f);
  GeoVector2F result = GeoVector2F_divideFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(1.0f), result));
}

TEST(C_GeoVector2F_Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_one();
  GeoVector2F_t result = GeoVector2F_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(2.0f), result));
}

TEST(C_GeoVector2F_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_one();
  GeoVector2F_t result = GeoVector2F_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_zero(), result));
}

TEST(C_GeoVector2F_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_uniform(2.0f);
  GeoVector2F_t result = GeoVector2F_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(4.0f), result));
}

TEST(C_GeoVector2F_Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2F_t test = GeoVector2F_uniform(2.0f);
  GeoVector2F_t result = GeoVector2F_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(1.0f), result));
}

TEST(C_GeoVector2F_Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector2F test = GeoVector2F_one();
  GeoVector2F result = GeoVector2F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(2.0f), result));
}

TEST(C_GeoVector2F_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector2F test = GeoVector2F_one();
  GeoVector2F result = GeoVector2F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(0.0f), result));
}

TEST(C_GeoVector2F_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector2F test = GeoVector2F_uniform(2.0f);
  GeoVector2F result = GeoVector2F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(4.0f), result));
}

TEST(C_GeoVector2F_Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector2F test = GeoVector2F_uniform(2.0f);
  GeoVector2F result = GeoVector2F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector2F_equal(GeoVector2F_uniform(1.0f), result));
}

TEST(C_GeoVector2F_Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector2F_t vec = GeoVector2F_one();
  vec = GeoVector2F_getNormalised(vec);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(C_GeoVector2F_Test, getMagnitudeReturnsCorrectLength) {
  GeoVector2F_t vec = GeoVector2F_one();
  vec = GeoVector2F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector2F_getMagnitude(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(C_GeoVector2F_Test, getLengthReturnsCorrectLength) {
  GeoVector2F_t vec = GeoVector2F_one();
  vec = GeoVector2F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector2F_getLength(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(C_GeoVector2F_Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector2F_t vec = GeoVector2F_create(0.0f, 1.0f);
  GeoVector2F_rotateToAngleAroundPoint(vec, 90.0f, GeoVector2F_zero());
  EXPECT_TRUE(GeoVector2F_epsilonEquals(vec, GeoVector2F_create(-1.0f, 0.0f), GeoVector2F_uniform(1e-7f)));
}
