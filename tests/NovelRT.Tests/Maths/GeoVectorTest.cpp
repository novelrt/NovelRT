// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVectorTest, geoVectorEqualityOperatorEvaluatesCorrectly) {
  EXPECT_EQ(GeoVector<float>(0.0f, 0.0f), GeoVector<float>(0.0f, 0.0f));
}

TEST(GeoVectorTest, geoVectorInequalityOperatorEvaluatesCorrectly) {
  EXPECT_NE(GeoVector<float>(0.0f, 0.0f), GeoVector<float>(1.0f, 0.0f));
}

TEST(GeoVectorTest, staticZeroCallReturnsGeoVectorZero) {
  EXPECT_EQ(GeoVector<float>::zero(), GeoVector<float>(0.0f, 0.0f));
}

TEST(GeoVectorTest, staticOneCallReturnsGeoVectorOne) {
  EXPECT_EQ(GeoVector<float>::one(), GeoVector<float>(1.0f, 1.0f));
}

TEST(GeoVectorTest, geoVectorAddOperatorAddsCorrectlyForGeoVector) {
  auto result = GeoVector<float>::one() + GeoVector<float>::one();
  EXPECT_EQ(result, GeoVector<float>(2.0f, 2.0f));
}

TEST(GeoVectorTest, geoVectorSubtractOperatorSubtractsCorrectlyForGeoVector) {
  auto result = GeoVector<float>::one() - GeoVector<float>::one();
  EXPECT_EQ(result, GeoVector<float>::zero());
}

TEST(GeoVectorTest, geoVectorMultiplyOperatorMultipliesCorrectlyForGeoVector) {
  auto result = GeoVector<float>(2.0f, 2.0f) * GeoVector<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector<float>(4.0f, 4.0f));
}

TEST(GeoVectorTest, geoVectorDivideOperatorDividesCorrectlyForGeoVector) {
  auto result = GeoVector<float>(2.0f, 2.0f) / GeoVector<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector<float>::one());
}

TEST(GeoVectorTest, geoVectorAddOperatorAddsCorrectlyForTemplateType) {
  auto result = GeoVector<float>::one() + 1.0f;
  EXPECT_EQ(result, GeoVector<float>(2.0f, 2.0f));
}

TEST(GeoVectorTest, geoVectorSubtractOperatorSubtractsCorrectlyForTemplateType) {
  auto result = GeoVector<float>::one() - 1.0f;
  EXPECT_EQ(result, GeoVector<float>::zero());
}

TEST(GeoVectorTest, geoVectorMultiplyOperatorMultipliesCorrectlyForTemplateType) {
  auto result = GeoVector<float>(2.0f, 2.0f) * 2.0f;
  EXPECT_EQ(result, GeoVector<float>(4.0f, 4.0f));
}

TEST(GeoVectorTest, geoVectorDivideOperatorDividesCorrectlyForTemplateType) {
  auto result = GeoVector<float>(2.0f, 2.0f) / 2.0f;
  EXPECT_EQ(result, GeoVector<float>::one());
}

TEST(GeoVectorTest, geoVectorAddAssignOperatorAddsAndAssignsCorrectlyForGeoVector) {
  auto result = GeoVector<float>::one();
  result += GeoVector<float>::one();
  EXPECT_EQ(result, GeoVector<float>(2.0f, 2.0f));
}

TEST(GeoVectorTest, geoVectorSubtractAssignOperatorSubtractsAndAssignsCorrectlyForGeoVector) {
  auto result = GeoVector<float>::one();
  result -= GeoVector<float>::one();
  EXPECT_EQ(result, GeoVector<float>::zero());
}

TEST(GeoVectorTest, geoVectorMultiplyAssignOperatorMultipliesAndAssignsCorrectlyForGeoVector) {
  auto result = GeoVector<float>(2.0f, 2.0f);
  result *= GeoVector<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector<float>(4.0f, 4.0f));
}

TEST(GeoVectorTest, geoVectorDivideAssignOperatorDividesAndAssignsCorrectlyForGeoVector) {
  auto result = GeoVector<float>(2.0f, 2.0f);
  result /= GeoVector<float>(2.0f, 2.0f);
  EXPECT_EQ(result, GeoVector<float>::one());
}

TEST(GeoVectorTest, geoVectorAddAssignOperatorAddsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector<float>::one();
  result += 1.0f;
  EXPECT_EQ(result, GeoVector<float>(2.0f, 2.0f));
}

TEST(GeoVectorTest, geoVectorSubtractAssignOperatorSubtractsAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector<float>::one();
  result -= 1.0f;
  EXPECT_EQ(result, GeoVector<float>::zero());
}

TEST(GeoVectorTest, geoVectorMultiplyAssignOperatorMultipliesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector<float>(2.0f, 2.0f);
  result *= 2.0f;
  EXPECT_EQ(result, GeoVector<float>(4.0f, 4.0f));
}

TEST(GeoVectorTest, geoVectorDivideAssignOperatorDividesAndAssignsCorrectlyForTemplateType) {
  auto result = GeoVector<float>(2.0f, 2.0f);
  result /= 2.0f;
  EXPECT_EQ(result, GeoVector<float>::one());
}

TEST(GeoVectorTest, geoVectorGetNormalisedReturnsNormalisedGeoVector) {
  auto vec = GeoVector<float>::one().getNormalised();
  float normalisedTotal = sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2));
  EXPECT_FLOAT_EQ(normalisedTotal, 1.0f);
}

TEST(GeoVectorTest, geoVectorGetMagnitudeReturnsCorrectLength) {
  auto vec = GeoVector<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getMagnitude(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVectorTest, geoVectorGetLengthReturnsCorrectLength) {
  auto vec = GeoVector<float>::one().getNormalised();
  EXPECT_FLOAT_EQ(vec.getLength(), sqrtf(powf(vec.getX(), 2) + powf(vec.getY(), 2)));
}

TEST(GeoVectorTest, geoVectorRotateToAngleAroundPointRotatesCorrectAmount) {
  auto vec = GeoVector<float>(0.0f, 1.0f);
  vec.rotateToAngleAroundPoint(90.0f, GeoVector<float>::zero());
  EXPECT_TRUE(vec.epsilonEquals(GeoVector<float>(-1.0f, 0.0f), GeoVector<float>(1e-7f, 1e-7f)));
}
