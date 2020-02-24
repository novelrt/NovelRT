// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoVectorTest, staticZeroCallReturnsGeoVectorZero) {
  EXPECT_EQ(GeoVector<float>::zero(), GeoVector<float>(0.0f, 0.0f));
}

TEST(GeoVectorTest, staticOneCallReturnsGeoVectorOne) {
  EXPECT_EQ(GeoVector<float>::one(), GeoVector<float>(1.0f, 1.0f));
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
