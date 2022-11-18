
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoBoundsTest, ctorCreatesObjectCorrectly)
{
    GeoBounds expectedBounds(GeoVector2F(1.0f, 1.0f), GeoVector2F(1.0f, 1.0f), 90.0f);

    EXPECT_EQ(expectedBounds.position, GeoVector2F::One());
    EXPECT_EQ(expectedBounds.size, GeoVector2F::One());
    EXPECT_FLOAT_EQ(expectedBounds.rotation, 90.0f);
}

TEST(GeoBoundsTest, pointIsWithinBoundsReturnsTrueWhenWithinBounds)
{
    GeoBounds bounds(GeoVector2F::Uniform(0.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds.pointIsWithinBounds(GeoVector2F::One()));
}

TEST(GeoBoundsTest, pointIsWithinBoundsReturnsFalseWhenNotWithinBounds)
{
    GeoBounds bounds(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds.pointIsWithinBounds(GeoVector2F::Uniform(10.0f)));
}

TEST(GeoBoundsTest, intersectsWithReturnsTrueWhenIntersecting)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(1.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds0.intersectsWith(bounds1));
}

TEST(GeoBoundsTest, intersectsWithReturnsTrueWhenIntersectingInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(1.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds1.intersectsWith(bounds0));
}

TEST(GeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersecting)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds0.intersectsWith(bounds1));
}

TEST(GeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersectingInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds1.intersectsWith(bounds0));
}

TEST(GeoBoundsTest, intersectsWithThrowExceptionWhenBoundsIsRotated)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 20.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_THROW(static_cast<void>(bounds0.intersectsWith(bounds1)), Exceptions::NotSupportedException);
}

TEST(GeoBoundsTest, intersectsWithThrowExceptionWhenBoundsIsRotatedInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 20.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_THROW(static_cast<void>(bounds1.intersectsWith(bounds0)), Exceptions::NotSupportedException);
}

TEST(GeoBoundsTest, getCornerInLocalSpaceReturnsCorrectValues)
{
    GeoBounds bounds(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(-2.5f), bounds.getCornerInLocalSpace(0));
    EXPECT_EQ(GeoVector2F(+2.5f, -2.5f), bounds.getCornerInLocalSpace(1));
    EXPECT_EQ(GeoVector2F::Uniform(+2.5f), bounds.getCornerInLocalSpace(2));
    EXPECT_EQ(GeoVector2F(-2.5f, +2.5f), bounds.getCornerInLocalSpace(3));
}

TEST(GeoBoundsTest, getCornerInWorldSpaceReturnsCorrectValues)
{
    GeoBounds bounds(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(-1.5f), bounds.getCornerInWorldSpace(0));
    EXPECT_EQ(GeoVector2F(+3.5f, -1.5f), bounds.getCornerInWorldSpace(1));
    EXPECT_EQ(GeoVector2F::Uniform(+3.5f), bounds.getCornerInWorldSpace(2));
    EXPECT_EQ(GeoVector2F(-1.5f, +3.5f), bounds.getCornerInWorldSpace(3));
}

TEST(GeoBoundsTest, getExtentsReturnsCorrectExtentsValue)
{
    GeoBounds bounds(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(2.5f), bounds.getExtents());
}

TEST(GeoBoundsTest, equalsOperatorReturnsTrueWhenBoundsAreEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(bounds0, bounds1);
}

TEST(GeoBoundsTest, equalsOperatorReturnsFalseWhenBoundsAreNotEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(10.0f), 0.0f);

    EXPECT_FALSE(bounds0 == bounds1);
}

TEST(GeoBoundsTest, notEqualsOperatorReturnsTrueWhenBoundsAreNotEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(10.0f), 0.0f);

    EXPECT_NE(bounds0, bounds1);
}

TEST(GeoBoundsTest, notEqualsOperatorReturnsFalseWhenBoundsAreEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds0 != bounds1);
}
