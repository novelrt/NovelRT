// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "../../../src/NovelRT.C/GeoVector2F.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

GeoVector2_t one = { 0.0f, 0.0f };
GeoVector2_t two = { 0.0f, 0.0f };
GeoVector2_t three = { 1.0f, 1.0f };

TEST(GeoVector2_C_Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_equal(one,two));
}

TEST(GeoVector2_C_Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_notEqual(one, three));
}

TEST(GeoVector2_C_Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_lessThan(one, three));
}

TEST(GeoVector2_C_Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_lessThanOrEqualTo(one, three));
  EXPECT_TRUE(GeoVector2F_lessThanOrEqualTo(three, three));
}

TEST(GeoVector2_C_Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_greaterThan(three, one));
}

TEST(GeoVector2_C_Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F_greaterThanOrEqualTo(three, one));
  EXPECT_TRUE(GeoVector2F_greaterThanOrEqualTo(three, three));
}
/*
TEST(GeoVector2_C_Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_EQ(GeoVector2<float>::uniform(1.0f), GeoVector2<float>(1.0f, 1.0f));
}

TEST(GeoVector2_C_Test, staticZeroCallReturnsGeoVector2Zero) {
  EXPECT_EQ(GeoVector2<float>::zero(), GeoVector2<float>::uniform(0.0f));
}

TEST(GeoVector2_C_Test, staticOneCallReturnsGeoVector2One) {
  EXPECT_EQ(GeoVector2<float>::one(), GeoVector2<float>::uniform(1.0f));
}

TEST(GeoVector2_C_Test, addOperatorAddsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() + GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::uniform(2.0f));
}

TEST(GeoVector2_C_Test, subtractOperatorSubtractsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() - GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2_C_Test, multiplyOperatorMultipliesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::uniform(2.0f) * GeoVector2<float>::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2<float>::uniform(4.0f));
}

TEST(GeoVector2_C_Test, divideOperatorDividesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::uniform(2.0f) / GeoVector2<float>::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2_C_Test, addOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::uniform(2.0f));
}

TEST(GeoVector2_C_Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2_C_Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::uniform(2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::uniform(4.0f));
}

TEST(GeoVector2_C_Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse) {
  auto result = 2.0f * GeoVector2<float>::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2<float>::uniform(4.0f));
}

TEST(GeoVector2_C_Test, divideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::uniform(2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2_C_Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result += GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::uniform(2.0f));
}

TEST(GeoVector2_C_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result -= GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2_C_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::uniform(2.0f);
  result *= GeoVector2<float>::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2<float>::uniform(4.0f));
}

TEST(GeoVector2_C_Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::uniform(2.0f);
  result /= GeoVector2<float>::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2_C_Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::uniform(2.0f));
}

TEST(GeoVector2_C_Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2_C_Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::uniform(2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::uniform(4.0f));
}

TEST(GeoVector2_C_Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::uniform(2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}*/

TEST(GeoVector2_C_Test, getNormalisedReturnsNormalisedGeoVector) {
  //replace with GeoVector2F::one().getNormalised or what the proper API is once completed.
  GeoVector2_t vec = GeoVector2F_getNormalised(three);
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2_C_Test, getMagnitudeReturnsCorrectLength) {
  //replace with GeoVector2F::one().getNormalised or what the proper API is once completed.
  GeoVector2_t vec = GeoVector2F_getNormalised(three);
  EXPECT_FLOAT_EQ(GeoVector2F_getMagnitude(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2_C_Test, getLengthReturnsCorrectLength) {
  //replace with GeoVector2F::one().getNormalised or what the proper API is once completed.
  GeoVector2_t vec = GeoVector2F_getNormalised(three);
  EXPECT_FLOAT_EQ(GeoVector2F_getLength(vec), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}
/*
TEST(GeoVector2_C_Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector2<float>(0.0f, 1.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector2<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector2<float>(-1.0f, 0.0f), GeoVector2<float>::uniform(1e-7f)));
}
*/
