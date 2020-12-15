// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector2Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector2F(0.0f, 0.0f), GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector2F(0.0f, 0.0f), GeoVector2F(1.0f, 0.0f));
}

TEST(GeoVector2Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) < GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F(0.0f, 0.0f) <= GeoVector2F(1.0f, 1.0f));
  EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) <= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) > GeoVector2F(0.0f, 0.0f));
}

TEST(GeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(0.0f, 0.0f));
  EXPECT_TRUE(GeoVector2F(1.0f, 1.0f) >= GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_EQ(GeoVector2F::uniform(1.0f), GeoVector2F(1.0f, 1.0f));
}

TEST(GeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  EXPECT_EQ(GeoVector2F::zero(), GeoVector2F::uniform(0.0f));
}

TEST(GeoVector2Test, staticOneCallReturnsGeoVector2One) {
  EXPECT_EQ(GeoVector2F::one(), GeoVector2F::uniform(1.0f));
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::one() + GeoVector2F::one();
  EXPECT_EQ(result, GeoVector2F::uniform(2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::one() - GeoVector2F::one();
  EXPECT_EQ(result, GeoVector2F::zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2) {
  auto result = GeoVector2F::uniform(2.0f) * GeoVector2F::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2F::uniform(4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2) {
  auto result = GeoVector2F::uniform(2.0f) / GeoVector2F::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2F::one());
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector2F::one() + 1.0f;
  EXPECT_EQ(result, GeoVector2F::uniform(2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector2F::one() - 1.0f;
  EXPECT_EQ(result, GeoVector2F::zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector2F::uniform(2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector2F::uniform(4.0f));
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse) {
  auto result = 2.0f * GeoVector2F::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2F::uniform(4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector2F::uniform(2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector2F::one());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::one();
  result += GeoVector2F::one();
  EXPECT_EQ(result, GeoVector2F::uniform(2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::one();
  result -= GeoVector2F::one();
  EXPECT_EQ(result, GeoVector2F::zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::uniform(2.0f);
  result *= GeoVector2F::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2F::uniform(4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2F::uniform(2.0f);
  result /= GeoVector2F::uniform(2.0f);
  EXPECT_EQ(result, GeoVector2F::one());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2F::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector2F::uniform(2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2F::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector2F::zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2F::uniform(2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector2F::uniform(4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2F::uniform(2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector2F::one());
}

TEST(GeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector2F::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.x, 2) + powf(vec.y, 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2Test, getMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector2F::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, getLengthReturnsCorrectLength) {
  auto vec = GeoVector2F::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.x, 2) + powf(vec.y, 2)));
}

TEST(GeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector2F(0.0f, 1.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector2F::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector2F(-1.0f, 0.0f), GeoVector2F::uniform(1e-7f)));
}
