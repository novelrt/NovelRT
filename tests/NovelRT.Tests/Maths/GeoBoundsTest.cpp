
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoBoundsTest, ctorCreatesObjectCorrectly) {
  GeoBounds expectedBounds(GeoVector2F(1.0f, 1.0f), GeoVector2F(1.0f, 1.0f), 90.0f);
  EXPECT_EQ(expectedBounds.position, GeoVector2F::one());
  EXPECT_EQ(expectedBounds.size, GeoVector2F::one());
  EXPECT_FLOAT_EQ(expectedBounds.rotation, 90.0f);
}

TEST(GeoBoundsTest, pointIsWithinBoundsReturnsTrueWhenWithinBounds) {
  GeoBounds bounds(GeoVector2F::uniform(0.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_TRUE(bounds.pointIsWithinBounds(GeoVector2F::one()));
}

TEST(GeoBoundsTest, pointIsWithinBoundsReturnsFalseWhenNotWithinBounds) {
  GeoBounds bounds(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_FALSE(bounds.pointIsWithinBounds(GeoVector2F::uniform(10.0f)));
}

TEST(GeoBoundsTest, intersectsWithReturnsTrueWhenIntersecting) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);
  GeoBounds bounds1(GeoVector2F::uniform(1.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_TRUE(bounds0.intersectsWith(bounds1));
}

TEST(GeoBoundsTest, intersectsWithReturnsTrueWhenIntersectingInversed) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);
  GeoBounds bounds1(GeoVector2F::uniform(1.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_TRUE(bounds1.intersectsWith(bounds0));
}

TEST(GeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersecting) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);
  GeoBounds bounds1(GeoVector2F::uniform(100.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_FALSE(bounds0.intersectsWith(bounds1));
}

TEST(GeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersectingInversed) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);
  GeoBounds bounds1(GeoVector2F::uniform(100.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_FALSE(bounds1.intersectsWith(bounds0));
}

TEST(GeoBoundsTest, intersectsWithThrowExceptionWhenBoundsIsRotated) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 20.0f);
  GeoBounds bounds1(GeoVector2F::uniform(100.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_THROW(bounds0.intersectsWith(bounds1), std::runtime_error);
}

TEST(GeoBoundsTest, intersectsWithThrowExceptionWhenBoundsIsRotatedInversed) {
  GeoBounds bounds0(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 20.0f);
  GeoBounds bounds1(GeoVector2F::uniform(100.0f), GeoVector2F::uniform(5.0f), 0.0f);
  EXPECT_THROW(bounds1.intersectsWith(bounds0), std::runtime_error);
}

TEST(GeoBoundsTest, getCornerInLocalSpaceReturnsCorrectValues) {
  GeoBounds bounds(GeoVector2F::zero(), GeoVector2F::uniform(5.0f), 0.0f);

  EXPECT_EQ(GeoVector2F::uniform(-2.5f), bounds.getCornerInLocalSpace(0));
  EXPECT_EQ(GeoVector2F(+2.5f, -2.5f), bounds.getCornerInLocalSpace(1));
  EXPECT_EQ(GeoVector2F::uniform(+2.5f), bounds.getCornerInLocalSpace(2));
  EXPECT_EQ(GeoVector2F(-2.5f, +2.5f), bounds.getCornerInLocalSpace(3));
}

TEST(GeoBoundsTest, getCornerInWorldSpaceReturnsCorrectValues) {
  GeoBounds bounds(GeoVector2F::one(), GeoVector2F::uniform(5.0f), 0.0f);

  EXPECT_EQ(GeoVector2F::uniform(-1.5f), bounds.getCornerInWorldSpace(0));
  EXPECT_EQ(GeoVector2F(+3.5f, -1.5f), bounds.getCornerInWorldSpace(1));
  EXPECT_EQ(GeoVector2F::uniform(+3.5f), bounds.getCornerInWorldSpace(2));
  EXPECT_EQ(GeoVector2F(-1.5f, +3.5f), bounds.getCornerInWorldSpace(3));
}