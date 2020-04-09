// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRTInterop/Maths/GeoVector4F_t.h"
#include "NovelRTInterop/Maths/GeoVector3F_t.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_equal({ 0.0f, 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_notEqual({ 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 0.0f, 0.0f, 0.0f }));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_lessThan({ 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_lessThanOrEqualTo({ 0.0f, 0.0f, 0.0f, 0.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));
  EXPECT_TRUE(GeoVector4F_lessThanOrEqualTo({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_greaterThan({ 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_greaterThanOrEqualTo({ 1.0f, 1.0f, 1.0f, 1.0f }, { 0.0f, 0.0f, 0.0f, 0.0f }));
  EXPECT_TRUE(GeoVector4F_greaterThanOrEqualTo({ 1.0f, 1.0f, 1.0f, 1.0f }, { 1.0f, 1.0f, 1.0f, 1.0f }));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector3WithUniformValues) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), { 1.0f, 1.0f, 1.0f, 1.0f }));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector3Zero) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_zero(), GeoVector4F_uniform(0.0f)));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector3One) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_one(), GeoVector4F_uniform(1.0f)));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector3) {
  GeoVector4F_t geo = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addVector(geo, geo);
  EXPECT_TRUE(GeoVector4F_equal(geo, GeoVector4F_uniform(2.0f)));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector3) {
  GeoVector4F_t geo = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subtractVector(geo, geo);
  EXPECT_TRUE(GeoVector4F_equal(geo, GeoVector4F_uniform(0.0f)));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(0.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyFloatIntoVectorInverse(2.0f, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(0.0f), result));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector4F_t vec = GeoVector4F_one();
  vec = GeoVector4F_getNormalised(vec);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength) {
  GeoVector4F_t vec = GeoVector4F_one();
  vec = GeoVector4F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector4F_getMagnitude(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength) {
  GeoVector4F_t vec = GeoVector4F_one();
  vec = GeoVector4F_getNormalised(vec);
  EXPECT_FLOAT_EQ(GeoVector4F_getLength(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2) + powf(vec.z, 2) + powf(vec.w, 2)));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector4F_t vec = GeoVector4F_create(0.0f, 1.0f, 0.0f, 0.0f);
  GeoVector4F_rotateToAngleAroundPoint(90.0f, vec, GeoVector3F_zero());
  EXPECT_TRUE(GeoVector4F_epsilonEquals(vec, GeoVector4F_create(-1.0f, 0.0f, 0.0f, 0.0f), GeoVector4F_uniform(1e-7f)));
}

TEST(InteropGeoVector4Test, geoVector2ConstructorReturnsCorrectGeoVector4) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_createFromGeoVector2F(GeoVector2F_uniform(1.0f)), { 1.0f, 1.0f, 0.0f, 0.0f }));
}

TEST(InteropGeoVector4Test, geoVector3ConstructorReturnsCorrectGeoVector4) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_createFromGeoVector3F({ 1.0f, 1.0f, 1.0f }), { 1.0f, 1.0f, 1.0f, 0.0f }));
}
