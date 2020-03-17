// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector3Test, geoVector3EqualityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector3<float>(0.0f, 0.0f, 0.0f), GeoVector3<float>(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, geoVector3InequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector3<float>(0.0f, 0.0f, 0.0f), GeoVector3<float>(1.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, geoVector3LessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3<float>::zero() < GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3LessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3<float>::zero() <= GeoVector3<float>::one());
  EXPECT_TRUE(GeoVector3<float>::one() <= GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3GreaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3<float>::one() > GeoVector3<float>::zero());
}

TEST(GeoVector3Test, geoVector3GreaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector3<float>::one() >= GeoVector3<float>::zero());
  EXPECT_TRUE(GeoVector3<float>::one() >= GeoVector3<float>::one());
}

TEST(GeoVector3Test, staticZeroCallReturnsGeoVector3Zero) {
  EXPECT_EQ(GeoVector3<float>::zero(), GeoVector3<float>(0.0f, 0.0f, 0.0f));
}

TEST(GeoVector3Test, staticOneCallReturnsGeoVector3One) {
  EXPECT_EQ(GeoVector3<float>::one(), GeoVector3<float>(1.0f, 1.0f, 1.0f));
}

TEST(GeoVector3Test, geoVector3AddOperatorAddsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>::one() + GeoVector3<float>::one();
  EXPECT_EQ(result, GeoVector3<float>(2.0f, 2.0f, 2.0f));
}

TEST(GeoVector3Test, geoVector3SubtractOperatorSubtractsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>::one() - GeoVector3<float>::one();
  EXPECT_EQ(result, GeoVector3<float>::zero());
}

TEST(GeoVector3Test, geoVector3MultiplyOperatorMultipliesCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f) * GeoVector3<float>(2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector3<float>(4.0f, 4.0f, 4.0f));
}

TEST(GeoVector3Test, geoVector3DivideOperatorDividesCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f) / GeoVector3<float>(2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3AddOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector3<float>(2.0f, 2.0f, 2.0f));
}

TEST(GeoVector3Test, geoVector3SubtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector3<float>::zero());
}

TEST(GeoVector3Test, geoVector3MultiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector3<float>(4.0f, 4.0f, 4.0f));
}

TEST(GeoVector3Test, geoVector3DivideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>::one();
  result += GeoVector3<float>::one();
  EXPECT_EQ(result, GeoVector3<float>(2.0f, 2.0f, 2.0f));
}

TEST(GeoVector3Test, geoVector3SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>::one();
  result -= GeoVector3<float>::one();
  EXPECT_EQ(result, GeoVector3<float>::zero());
}

TEST(GeoVector3Test, geoVector3MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f);
  result *= GeoVector3<float>(2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector3<float>(4.0f, 4.0f, 4.0f));
}

TEST(GeoVector3Test, geoVector3DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector3) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f);
  result /= GeoVector3<float>(2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3AddAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector3<float>(2.0f, 2.0f, 2.0f));
}

TEST(GeoVector3Test, geoVector3SubtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector3<float>::zero());
}

TEST(GeoVector3Test, geoVector3MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector3<float>(4.0f, 4.0f, 4.0f));
}

TEST(GeoVector3Test, geoVector3DivideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector3<float>(2.0f, 2.0f, 2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector3<float>::one());
}

TEST(GeoVector3Test, geoVector3GetNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector3<float>::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector3Test, geoVector3GetMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector3<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(GeoVector3Test, geoVector3GetLengthReturnsCorrectLength) {
  auto vec = GeoVector3<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2)));
}

TEST(GeoVector3Test, geoVector3RotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector3<float>(0.0f, 1.0f, 0.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector3<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector3<float>(-1.0f, 0.0f, 0.0f), GeoVector3<float>(1e-7f, 1e-7f, 1e-7f)));
}
