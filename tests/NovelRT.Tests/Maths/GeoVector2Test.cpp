// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector2Test, equalityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector2<float>(0.0f, 0.0f), GeoVector2<float>(0.0f, 0.0f));
}

TEST(GeoVector2Test, inequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector2<float>(0.0f, 0.0f), GeoVector2<float>(1.0f, 0.0f));
}

TEST(GeoVector2Test, lessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::zero() < GeoVector2<float>::one());
}

TEST(GeoVector2Test, lessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::zero() <= GeoVector2<float>::one());
  EXPECT_TRUE(GeoVector2<float>::one() <= GeoVector2<float>::one());
}

TEST(GeoVector2Test, greaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::one() > GeoVector2<float>::zero());
}

TEST(GeoVector2Test, greaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::one() >= GeoVector2<float>::zero());
  EXPECT_TRUE(GeoVector2<float>::one() >= GeoVector2<float>::one());
}

TEST(GeoVector2Test, staticUniformCallReturnsGeoVector2WithUniformValues) {
  EXPECT_EQ(GeoVector2<float>(1.0f, 1.0f), GeoVector2<float>::uniform(1.0f));
}

TEST(GeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  EXPECT_EQ(GeoVector2<float>::zero(), GeoVector2<float>(0.0f, 0.0f));
}

TEST(GeoVector2Test, staticOneCallReturnsGeoVector2One) {
  EXPECT_EQ(GeoVector2<float>::one(), GeoVector2<float>(1.0f, 1.0f));
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() + GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() - GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f) * GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f) / GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, addOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, subtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, multiplyOperatorMultipliesCorrectlyForTemplateTypeInverse) {
  auto result = 2.0f * GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, divideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result += GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result -= GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result *= GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result /= GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, addAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, subtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, multiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, divideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, getNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector2<float>::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2Test, getMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector2<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVector2Test, getLengthReturnsCorrectLength) {
  auto vec = GeoVector2<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVector2Test, rotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector2<float>(0.0f, 1.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector2<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector2<float>(-1.0f, 0.0f), GeoVector2<float>(1e-7f, 1e-7f)));
}
