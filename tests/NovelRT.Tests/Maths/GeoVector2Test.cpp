// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector2Test, geoVector2EqualityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector2<float>(0.0f, 0.0f), GeoVector2<float>(0.0f, 0.0f));
}

TEST(GeoVector2Test, geoVector2InequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector2<float>(0.0f, 0.0f), GeoVector2<float>(1.0f, 0.0f));
}

TEST(GeoVector2Test, geoVector2LessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::zero() < GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2LessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::zero() <= GeoVector2<float>::one());
  EXPECT_TRUE(GeoVector2<float>::one() <= GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2GreaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::one() > GeoVector2<float>::zero());
}

TEST(GeoVector2Test, geoVector2GreaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector2<float>::one() >= GeoVector2<float>::zero());
  EXPECT_TRUE(GeoVector2<float>::one() >= GeoVector2<float>::one());
}

TEST(GeoVector2Test, staticZeroCallReturnsGeoVector2Zero) {
  EXPECT_EQ(GeoVector2<float>::zero(), GeoVector2<float>(0.0f, 0.0f));
}

TEST(GeoVector2Test, staticOneCallReturnsGeoVector2One) {
  EXPECT_EQ(GeoVector2<float>::one(), GeoVector2<float>(1.0f, 1.0f));
}

TEST(GeoVector2Test, geoVector2AddOperatorAddsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() + GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, geoVector2SubtractOperatorSubtractsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one() - GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, geoVector2MultiplyOperatorMultipliesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f) * GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, geoVector2DivideOperatorDividesCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f) / GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2AddOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, geoVector2SubtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, geoVector2MultiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, geoVector2DivideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result += GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, geoVector2SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>::one();
  result -= GeoVector2<float>::one();
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, geoVector2MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result *= GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, geoVector2DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector2) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result /= GeoVector2<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2AddAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector2<float>(2.0f, 2.0f));
}

TEST(GeoVector2Test, geoVector2SubtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector2<float>::zero());
}

TEST(GeoVector2Test, geoVector2MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>(4.0f, 4.0f));
}

TEST(GeoVector2Test, geoVector2DivideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector2<float>(2.0f, 2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector2<float>::one());
}

TEST(GeoVector2Test, geoVector2GetNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector2<float>::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector2Test, geoVector2GetMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector2<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVector2Test, geoVector2GetLengthReturnsCorrectLength) {
  auto vec = GeoVector2<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVector2Test, geoVector2RotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector2<float>(0.0f, 1.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector2<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector2<float>(-1.0f, 0.0f), GeoVector2<float>(1e-7f, 1e-7f)));
}
