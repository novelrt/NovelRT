
// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(GeoBoundsTest, CtorCreatesObjectCorrectly)
{
    GeoBounds expectedBounds(GeoVector2F(1.0f, 1.0f), GeoVector2F(1.0f, 1.0f), 90.0f);

    EXPECT_EQ(expectedBounds.position, GeoVector2F::One());
    EXPECT_EQ(expectedBounds.size, GeoVector2F::One());
    EXPECT_FLOAT_EQ(expectedBounds.rotation, 90.0f);
}

TEST(GeoBoundsTest, PointIsWithinBoundsReturnsTrueWhenWithinBounds)
{
    GeoBounds bounds(GeoVector2F::Uniform(0.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds.PointIsWithinBounds(GeoVector2F::One()));
}

TEST(GeoBoundsTest, PointIsWithinBoundsReturnsFalseWhenNotWithinBounds)
{
    GeoBounds bounds(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds.PointIsWithinBounds(GeoVector2F::Uniform(10.0f)));
}

TEST(GeoBoundsTest, IntersectsWithReturnsTrueWhenIntersecting)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(1.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds0.IntersectsWith(bounds1));
}

TEST(GeoBoundsTest, IntersectsWithReturnsTrueWhenIntersectingInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(1.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_TRUE(bounds1.IntersectsWith(bounds0));
}

TEST(GeoBoundsTest, IntersectsWithReturnsFalseWhenNotIntersecting)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds0.IntersectsWith(bounds1));
}

TEST(GeoBoundsTest, IntersectsWithReturnsFalseWhenNotIntersectingInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds1.IntersectsWith(bounds0));
}

TEST(GeoBoundsTest, IntersectsWithThrowExceptionWhenBoundsIsRotated)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 20.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_THROW(static_cast<void>(bounds0.IntersectsWith(bounds1)), Exceptions::NotSupportedException);
}

TEST(GeoBoundsTest, IntersectsWithThrowExceptionWhenBoundsIsRotatedInversed)
{
    GeoBounds bounds0(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 20.0f);
    GeoBounds bounds1(GeoVector2F::Uniform(100.0f), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_THROW(static_cast<void>(bounds1.IntersectsWith(bounds0)), Exceptions::NotSupportedException);
}

TEST(GeoBoundsTest, GetCornerInLocalSpaceReturnsCorrectValues)
{
    GeoBounds bounds(GeoVector2F::Zero(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(-2.5f), bounds.GetCornerInLocalSpace(0));
    EXPECT_EQ(GeoVector2F(+2.5f, -2.5f), bounds.GetCornerInLocalSpace(1));
    EXPECT_EQ(GeoVector2F::Uniform(+2.5f), bounds.GetCornerInLocalSpace(2));
    EXPECT_EQ(GeoVector2F(-2.5f, +2.5f), bounds.GetCornerInLocalSpace(3));
}

TEST(GeoBoundsTest, GetCornerInWorldSpaceReturnsCorrectValues)
{
    GeoBounds bounds(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(-1.5f), bounds.GetCornerInWorldSpace(0));
    EXPECT_EQ(GeoVector2F(+3.5f, -1.5f), bounds.GetCornerInWorldSpace(1));
    EXPECT_EQ(GeoVector2F::Uniform(+3.5f), bounds.GetCornerInWorldSpace(2));
    EXPECT_EQ(GeoVector2F(-1.5f, +3.5f), bounds.GetCornerInWorldSpace(3));
}

TEST(GeoBoundsTest, GetExtentsReturnsCorrectExtentsValue)
{
    GeoBounds bounds(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(GeoVector2F::Uniform(2.5f), bounds.GetExtents());
}

TEST(GeoBoundsTest, EqualsOperatorReturnsTrueWhenBoundsAreEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_EQ(bounds0, bounds1);
}

TEST(GeoBoundsTest, EqualsOperatorReturnsFalseWhenBoundsAreNotEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(10.0f), 0.0f);

    EXPECT_FALSE(bounds0 == bounds1);
}

TEST(GeoBoundsTest, NotEqualsOperatorReturnsTrueWhenBoundsAreNotEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(10.0f), 0.0f);

    EXPECT_NE(bounds0, bounds1);
}

TEST(GeoBoundsTest, NotEqualsOperatorReturnsFalseWhenBoundsAreEqual)
{
    GeoBounds bounds0(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);
    GeoBounds bounds1(GeoVector2F::One(), GeoVector2F::Uniform(5.0f), 0.0f);

    EXPECT_FALSE(bounds0 != bounds1);
}
