// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/GeoVector3F_t.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

GeoVector3F_t vec3One = GeoVector3F_uniform(0.0);
GeoVector3F_t vec3Two = GeoVector3F_uniform(0.0f);
GeoVector3F_t vec3Three = GeoVector3F_uniform(1.0f);

TEST(InteropGeoVector3Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_equal(vec3One, vec3Two));
}

TEST(InteropGeoVector3Test, createReturnsCorrectGeoVector3) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_t{1.0f, 1.0f, 1.0f}, GeoVector3F_create(1.0f, 1.0f, 1.0f)));
}

TEST(InteropGeoVector3Test, createFromGeoVector2ReturnsCorrectGeoVector3) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_createFromGeoVector2F(GeoVector2F_create(1.0f, 1.0f)), GeoVector3F_t{1.0f, 1.0f, 0.0f}));
}

TEST(InteropGeoVector3Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_notEqual(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_lessThan(vec3One, vec3Three));
}

TEST(InteropGeoVector3Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_lessThanOrEqualTo(vec3One, vec3Three));
  EXPECT_TRUE(GeoVector3F_lessThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_greaterThan(vec3Three, vec3One));
}

TEST(InteropGeoVector3Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3One));
  EXPECT_TRUE(GeoVector3F_greaterThanOrEqualTo(vec3Three, vec3Three));
}

TEST(InteropGeoVector3Test, staticUniformCallReturnsGeoVector3WithUniformValues) {
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), vec3Three));
}

TEST(InteropGeoVector3Test, staticZeroCallReturnsGeoVector3Zero) {
  GeoVector3F_t test = GeoVector3F_create(0.0f, 0.0f, 0.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, staticOneCallReturnsGeoVector3One) {
  GeoVector3F_t test = GeoVector3F_create(1.0f, 1.0f, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_one(), test));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subtractVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_zero(), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(InteropGeoVector3Test, addOperatorAddsCorrectlyForFloatType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_addFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), result));
}

TEST(InteropGeoVector3Test, subtractOperatorSubtractsCorrectlyForFloatType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_t result = GeoVector3F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(0.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloatType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, multiplyOperatorMultipliesCorrectlyForFloatTypeInverse) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_multiplyFloatInverse(2.0f, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), result));
}

TEST(InteropGeoVector3Test, divideOperatorDividesCorrectlyForFloatType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_t result = GeoVector3F_divideFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), result));
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_zero(), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3F) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(2.0f), test));
}

TEST(InteropGeoVector3Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_one();
  GeoVector3F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(0.0f), test));
}

TEST(InteropGeoVector3Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(4.0f), test));
}

TEST(InteropGeoVector3Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector3F_t test = GeoVector3F_uniform(2.0f);
  GeoVector3F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector3F_equal(GeoVector3F_uniform(1.0f), test));
}

TEST(InteropGeoVector3Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector3F_t cVector = GeoVector3F_one();
  GeoVector3F_t normal = GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector3Test, getMagnitudeReturnsCorrectLength) {
  GeoVector3F_t cVector = GeoVector3F_one();
  GeoVector3F_t normal = GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  EXPECT_FLOAT_EQ(GeoVector3F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(InteropGeoVector3Test, getLengthReturnsCorrectLength) {
  GeoVector3F_t cVector = GeoVector3F_one();
  GeoVector3F_t normal = GeoVector3F_getNormalised(cVector);
  GeoVector3<float>& vec = reinterpret_cast<GeoVector3<float>&>(normal);
  EXPECT_FLOAT_EQ(GeoVector3F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(InteropGeoVector3Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector3F_t vec = GeoVector3F_create(0.0f, 1.0f, 0.0f);
  GeoVector3F_t zero = GeoVector3F_zero();
  GeoVector3F_rotateToAngleAroundPoint(vec, 90.0f, zero);
  GeoVector3F_t other = GeoVector3F_create(-1.0f, 0.0f, 0.0f);
  GeoVector3F_t epsilon = GeoVector3F_uniform(1e-7f);

  EXPECT_TRUE(GeoVector3F_epsilonEquals(vec, other, epsilon));
}