// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVector4Test, geoVector4EqualityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector4<float>(0.0f, 0.0f, 0.0f, 0.0f), GeoVector4<float>(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, geoVector4InequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector4<float>(0.0f, 0.0f, 0.0f, 0.0f), GeoVector4<float>(1.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, geoVector4LessThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4<float>::zero() < GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4LessOrEqualToThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4<float>::zero() <= GeoVector4<float>::one());
  EXPECT_TRUE(GeoVector4<float>::one() <= GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4GreaterThanOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4<float>::one() > GeoVector4<float>::zero());
}

TEST(GeoVector4Test, geoVector4GreaterThanOrEqualToOperatorEvaluatesCorrectly) {
  EXPECT_TRUE(GeoVector4<float>::one() >= GeoVector4<float>::zero());
  EXPECT_TRUE(GeoVector4<float>::one() >= GeoVector4<float>::one());
}

TEST(GeoVector4Test, staticZeroCallReturnsGeoVector4Zero) {
  EXPECT_EQ(GeoVector4<float>::zero(), GeoVector4<float>(0.0f, 0.0f, 0.0f, 0.0f));
}

TEST(GeoVector4Test, staticOneCallReturnsGeoVector4One) {
  EXPECT_EQ(GeoVector4<float>::one(), GeoVector4<float>(1.0f, 1.0f, 1.0f, 1.0f));
}

TEST(GeoVector4Test, geoVector4AddOperatorAddsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>::one() + GeoVector4<float>::one();
  EXPECT_EQ(result, GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST(GeoVector4Test, geoVector4SubtractOperatorSubtractsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>::one() - GeoVector4<float>::one();
  EXPECT_EQ(result, GeoVector4<float>::zero());
}

TEST(GeoVector4Test, geoVector4MultiplyOperatorMultipliesCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f) * GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector4<float>(4.0f, 4.0f, 4.0f, 4.0f));
}

TEST(GeoVector4Test, geoVector4DivideOperatorDividesCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f) / GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4AddOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST(GeoVector4Test, geoVector4SubtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector4<float>::zero());
}

TEST(GeoVector4Test, geoVector4MultiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector4<float>(4.0f, 4.0f, 4.0f, 4.0f));
}

TEST(GeoVector4Test, geoVector4DivideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4AddAssignOperatorAddsAndAssignsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>::one();
  result += GeoVector4<float>::one();
  EXPECT_EQ(result, GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST(GeoVector4Test, geoVector4SubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>::one();
  result -= GeoVector4<float>::one();
  EXPECT_EQ(result, GeoVector4<float>::zero());
}

TEST(GeoVector4Test, geoVector4MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  result *= GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector4<float>(4.0f, 4.0f, 4.0f, 4.0f));
}

TEST(GeoVector4Test, geoVector4DivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector4) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  result /= GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4AddAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f));
}

TEST(GeoVector4Test, geoVector4SubtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector4<float>::zero());
}

TEST(GeoVector4Test, geoVector4MultiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector4<float>(4.0f, 4.0f, 4.0f, 4.0f));
}

TEST(GeoVector4Test, geoVector4DivideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector4<float>(2.0f, 2.0f, 2.0f, 2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector4<float>::one());
}

TEST(GeoVector4Test, geoVector4GetNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector4<float>::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVector4Test, geoVector4GetMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector4<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(GeoVector4Test, geoVector4GetLengthReturnsCorrectLength) {
  auto vec = GeoVector4<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2) + powf(vec.getZ(), 2) + powf(vec.getW(), 2)));
}

TEST(GeoVector4Test, geoVector4RotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector4<float>(0.0f, 1.0f, 0.0f, 0.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector4<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector4<float>(-1.0f, 0.0f, 0.0f, 0.0f), GeoVector4<float>(1e-7f, 1e-7f, 1e-7f, 1e-7f)));
}
