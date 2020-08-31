
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
    GeoBounds bounds(GeoVector2F::uniform(0.0f), GeoVector2F::uniform(5.0f), 0.0f);
    EXPECT_FALSE(bounds.pointIsWithinBounds(GeoVector2F::uniform(10.0f)));
}

TEST(GeoBoundsTest, intersectsWithReturnsTrueWhenIntersecting) {
    GeoBounds bounds0(GeoVector2F::uniform(0.0f), GeoVector2F::uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::uniform(1.0f), GeoVector2F::uniform(5.0f), 0.0f);
    EXPECT_TRUE(bounds0.intersectsWith(bounds1));
}