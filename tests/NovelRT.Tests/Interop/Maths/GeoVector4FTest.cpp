// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/GeoVector4F_t.h"
#include "NovelRT.Interop/Maths/GeoVector3F_t.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

GeoVector4F_t vec4One = GeoVector4F_uniform(0.0);
GeoVector4F_t vec4Two = GeoVector4F_uniform(0.0f);
GeoVector4F_t vec4Three = GeoVector4F_uniform(1.0f);

TEST(InteropGeoVector4Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_equal(vec4One, vec4Two));
}

TEST(InteropGeoVector4Test, createReturnsCorrectGeoVector4) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_t{1.0f, 1.0f, 1.0f, 1.0f}, GeoVector4F_create(1.0f, 1.0f, 1.0f, 1.0f)));
}

TEST(InteropGeoVector4Test, createFromGeoVector2ReturnsCorrectGeoVector3) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_createFromGeoVector2F(GeoVector2F_create(1.0f, 1.0f)), GeoVector4F_t{1.0f, 1.0f, 0.0f, 0.0f}));
}

TEST(InteropGeoVector4Test, createFromGeoVector3ReturnsCorrectGeoVector4) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_createFromGeoVector3F(GeoVector3F_create(1.0f, 1.0f, 1.0f)), GeoVector4F_t{1.0f, 1.0f, 1.0f, 0.0f}));
}

TEST(InteropGeoVector4Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_notEqual(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_lessThan(vec4One, vec4Three));
}

TEST(InteropGeoVector4Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_lessThanOrEqualTo(vec4One, vec4Three));
  EXPECT_TRUE(GeoVector4F_lessThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_greaterThan(vec4Three, vec4One));
}

TEST(InteropGeoVector4Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4One));
  EXPECT_TRUE(GeoVector4F_greaterThanOrEqualTo(vec4Three, vec4Three));
}

TEST(InteropGeoVector4Test, staticUniformCallReturnsGeoVector3WithUniformValues) {
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), vec4Three));
}

TEST(InteropGeoVector4Test, staticZeroCallReturnsGeoVector3Zero) {
  GeoVector4F_t test = GeoVector4F_create(0.0f, 0.0f, 0.0f, 0.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, staticOneCallReturnsGeoVector3One) {
  GeoVector4F_t test = GeoVector4F_create(1.0f, 1.0f, 1.0f, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_one(), test));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subtractVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_zero(), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, addOperatorAddsCorrectlyForFloatType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_addFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), result));
}

TEST(InteropGeoVector4Test, subtractOperatorSubtractsCorrectlyForFloatType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_t result = GeoVector4F_subtractFloat(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(0.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloatType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, multiplyOperatorMultipliesCorrectlyForFloatTypeInverse) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_multiplyFloatInverse(2.0f, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), result));
}

TEST(InteropGeoVector4Test, divideOperatorDividesCorrectlyForFloatType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_t result = GeoVector4F_divideFloat(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), result));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_addIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_subtractFromVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_zero(), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_multiplyIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4F) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_divideIntoVector(test, test);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_addFloatIntoVector(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(2.0f), test));
}

TEST(InteropGeoVector4Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_one();
  GeoVector4F_subFloatFromVector(test, 1.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(0.0f), test));
}

TEST(InteropGeoVector4Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_multiplyFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(4.0f), test));
}

TEST(InteropGeoVector4Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  GeoVector4F_t test = GeoVector4F_uniform(2.0f);
  GeoVector4F_divideFloatIntoVector(test, 2.0f);
  EXPECT_TRUE(GeoVector4F_equal(GeoVector4F_uniform(1.0f), test));
}

TEST(InteropGeoVector4Test, getNormalisedReturnsNormalisedGeoVector) {
  GeoVector4F_t cVector = GeoVector4F_one();
  GeoVector4F_t normal = GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(InteropGeoVector4Test, getMagnitudeReturnsCorrectLength) {
  GeoVector4F_t cVector = GeoVector4F_one();
  GeoVector4F_t normal = GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  EXPECT_FLOAT_EQ(GeoVector4F_getMagnitude(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(InteropGeoVector4Test, getLengthReturnsCorrectLength) {
  GeoVector4F_t cVector = GeoVector4F_one();
  GeoVector4F_t normal = GeoVector4F_getNormalised(cVector);
  GeoVector4<float>& vec = reinterpret_cast<GeoVector4<float>&>(normal);
  EXPECT_FLOAT_EQ(GeoVector4F_getLength(normal), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(InteropGeoVector4Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  GeoVector4F_t vec = GeoVector4F_create(0.0f, 1.0f, 0.0f, 0.0f);
  GeoVector3F_t zero = GeoVector3F_zero();
  GeoVector4F_rotateToAngleAroundPoint(vec, 90.0f, zero);
  GeoVector4F_t other = GeoVector4F_create(-1.0f, 0.0f, 0.0f, 0.0f);
  GeoVector4F_t epsilon = GeoVector4F_uniform(1e-7f);

  EXPECT_TRUE(GeoVector4F_epsilonEquals(vec, other, epsilon));
}

