// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRTInterop/GeoVector3F.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(C_GeoVector3F_Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_equal({ 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }));
}

TEST(C_GeoVector3F_Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_notEqual({ 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f }));
}

TEST(C_GeoVector3F_Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_lessThan({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
}

TEST(C_GeoVector3F_Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_lessThanOrEqualTo({ 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f }));
  EXPECT_TRUE(GeoVector3F_lessThanOrEqualTo({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }));
}

TEST(C_GeoVector3F_Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_greaterThan({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
}

TEST(C_GeoVector3F_Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_greaterThanOrEqualTo({ 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f }));
  EXPECT_TRUE(GeoVector3F_greaterThanOrEqualTo({ 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }));
}

TEST(C_GeoVector3F_Test, staticUniformCallReturnsGeoVector3WithUniformValues) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), { 1.0f, 1.0f, 1.0f }));
}

TEST(C_GeoVector3F_Test, staticZeroCallReturnsGeoVector3Zero) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_zero(), GeoVector3F_uniform(0.0f)));
}

TEST(C_GeoVector3F_Test, staticOneCallReturnsGeoVector3One) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_one(), GeoVector3F_uniform(1.0f)));
}

TEST(C_GeoVector3F_Test, addOperatorAddsCorrectlyForGeoVector3) {
  GeoVector3F_t geo = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addVector(geo, geo);
  EXPECT_TRUE(GeoVector3F_equal(geo, GeoVector3F_uniform(2.0f)));
}

TEST(C_GeoVector3F_Test, subtractOperatorSubtractsCorrectlyForGeoVector3) {
  GeoVector3F_t geo = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subtractVector(geo, geo);
  EXPECT_TRUE(GeoVector3F_equal(geo, GeoVector3F_uniform(0.0f)));
}

TEST(C_GeoVector3F_Test, multiplyOperatorMultipliesCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(C_GeoVector3F_Test, divideOperatorDividesCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(C_GeoVector3F_Test, addOperatorAddsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), result));
}

TEST(C_GeoVector3F_Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(0.0f), result));
}

TEST(C_GeoVector3F_Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(C_GeoVector3F_Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyFloatIntoVectorInverse(2.0f, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(C_GeoVector3F_Test, divideOperatorDividesCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(C_GeoVector3F_Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), result));
}

TEST(C_GeoVector3F_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_zero(), result));
}

TEST(C_GeoVector3F_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(C_GeoVector3F_Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(C_GeoVector3F_Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), result));
}

TEST(C_GeoVector3F_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(0.0f), result));
}

TEST(C_GeoVector3F_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(C_GeoVector3F_Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(C_GeoVector3F_Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector3F_t vec = GeoVector3F_one();
  vec = GeoVector3F_getNormalised(vec);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(C_GeoVector3F_Test, getMagnitudeReturnsCorrectLength) {
  GeoVector3F_t vec = GeoVector3F_one();
  vec = GeoVector3F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector3F_getMagnitude(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(C_GeoVector3F_Test, getLengthReturnsCorrectLength) {
  GeoVector3F_t vec = GeoVector3F_one();
  vec = GeoVector3F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector3F_getLength(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2)));
}

TEST(C_GeoVector3F_Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector3F_t vec = GeoVector3F_create(0.0f, 1.0f, 0.0f);
  GeoVector3F_rotateToAngleAroundPoint(90.0f, vec, GeoVector3F_zero());
  EXPECT_TRUE(GeoVector3F_epsilonEquals(vec, GeoVector3F_create(-1.0f, 0.0f, 0.0f), GeoVector3F_uniform(1e-7f)));
}

TEST(C_GeoVector3F_Test, geoVector2ConstructorReturnsCorrectGeoVector3) {
  //EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_createFromGeoVector2F({ 1.0f, 1.0f }), { 1.0f, 1.0f, 0.0f }));
}
