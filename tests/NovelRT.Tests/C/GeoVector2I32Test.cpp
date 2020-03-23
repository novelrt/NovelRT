// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelC/GeoVector2I32.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

GeoVector2I32_t one = { 0, 0 };
GeoVector2I32_t two = { 0, 0 };
GeoVector2I32_t three = { 1, 1 };

TEST(C_GeoVector2I32_Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_equal(one,two));
}

TEST(C_GeoVector2I32_Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_notEqual(one, three));
}

TEST(C_GeoVector2I32_Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_lessThan(one, three));
}

TEST(C_GeoVector2I32_Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_lessThanOrEqualTo(one, three));
  EXPECT_TRUE(GeoVector2I32_lessThanOrEqualTo(three, three));
}

TEST(C_GeoVector2I32_Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_greaterThan(three, one));
}

TEST(C_GeoVector2I32_Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2I32_greaterThanOrEqualTo(three, one));
  EXPECT_TRUE(GeoVector2I32_greaterThanOrEqualTo(three, three));
}

TEST(C_GeoVector2I32_Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(1), three));
}

TEST(C_GeoVector2I32_Test, staticZeroCallReturnsGeoVector2Zero) {
  GeoVector2I32_t test = GeoVector2I32_create(0, 0);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_zero(), test));
}

TEST(C_GeoVector2I32_Test, staticOneCallReturnsGeoVector2One) {
  GeoVector2I32_t test = GeoVector2I32_create(1, 1);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_one(), test));
}

TEST(C_GeoVector2I32_Test, addOperatorAddsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_addVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(2), result));
}

TEST(C_GeoVector2I32_Test, subtractOperatorSubtractsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_subtractVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_zero(), result));
}

TEST(C_GeoVector2I32_Test, multiplyOperatorMultipliesCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(4), result));
}

TEST(C_GeoVector2I32_Test, divideOperatorDividesCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_divideVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(1), result));
}

TEST(C_GeoVector2I32_Test, addOperatorAddsCorrectlyForFloatType) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_addI32(test, 1);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(2), result));
}

TEST(C_GeoVector2I32_Test, subtractOperatorSubtractsCorrectlyForFloatType) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_subtractI32(test, 1);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(0), result));
}

TEST(C_GeoVector2I32_Test, multiplyOperatorMultipliesCorrectlyForFloatType) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_multiplyI32(test, 2);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(4), result));
}

TEST(C_GeoVector2I32_Test, multiplyOperatorMultipliesCorrectlyForFloatTypeInverse) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_multiplyI32IntoVectorInverse(2, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(4), result));
}

TEST(C_GeoVector2I32_Test, divideOperatorDividesCorrectlyForFloatType) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_divideI32(test, 2);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(1), result));
}

TEST(C_GeoVector2I32_Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(2), result));
}

TEST(C_GeoVector2I32_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_zero(), result));
}

TEST(C_GeoVector2I32_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(4), result));
}

TEST(C_GeoVector2I32_Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2F) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(1), result));
}

TEST(C_GeoVector2I32_Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_addI32IntoVector(test, 1);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(2), result));
}

TEST(C_GeoVector2I32_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector2I32_t test = GeoVector2I32_one();
  GeoVector2I32_t result = GeoVector2I32_subI32FromVector(test, 1);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(0), result));
}

TEST(C_GeoVector2I32_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_multiplyI32IntoVector(test, 2);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(4), result));
}

TEST(C_GeoVector2I32_Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector2I32_t test = GeoVector2I32_uniform(2);
  GeoVector2I32_t result = GeoVector2I32_divideI32IntoVector(test, 2);
  EXPECT_TRUE(GeoVector2I32_equal(GeoVector2I32_uniform(1), result));
}

TEST(C_GeoVector2I32_Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector2I32_t vec = GeoVector2I32_one();
  vec = GeoVector2I32_getNormalised(vec);
  float normalisedTotal = sqrtf(powf(static_cast<float>(vec.x), 2) + powf(static_cast<float>(vec.y), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1);
}

TEST(C_GeoVector2I32_Test, getMagnitudeReturnsCorrectLength) {
  GeoVector2I32_t vec = GeoVector2I32_one();
  vec = GeoVector2I32_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector2I32_getMagnitude(vec), sqrtf(powf(static_cast<float>(vec.x), 2) + powf(static_cast<float>(vec.y), 2)));
}

TEST(C_GeoVector2I32_Test, getLengthReturnsCorrectLength) {
  GeoVector2I32_t vec = GeoVector2I32_one();
  vec = GeoVector2I32_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector2I32_getLength(vec), sqrtf(powf(static_cast<float>(vec.x), 2) + powf(static_cast<float>(vec.y), 2)));
}

TEST(C_GeoVector2I32_Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector2I32_t vec = GeoVector2I32_create(0, 1);
  GeoVector2I32_rotateToAngleAroundPoint(vec, 90.0f, GeoVector2I32_zero());
  EXPECT_TRUE(GeoVector2I32_epsilonEquals(vec, GeoVector2I32_create(-1, 0), GeoVector2I32_uniform(static_cast<int32_t>(1e-7f))));
}
