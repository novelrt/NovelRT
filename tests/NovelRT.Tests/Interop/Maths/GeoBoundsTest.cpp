// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoBounds.h>
#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoBoundsTest, zeroReturnsZeroedOutGeoBounds)
{
    NrtGeoBounds expectedBounds{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_equal(expectedBounds, Nrt_GeoBounds_zero()));
}

TEST(InteropGeoBoundsTest, equalsOperatorReturnsTrueWhenBoundsAreEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, equalsOperatorReturnsFalseWhenBoundsAreNotEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(10.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, notEqualsOperatorReturnsFalseWhenBoundsAreEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_notEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, notEqualsOperatorReturnsTrueWhenBoundsAreNotEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(10.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_notEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, getCornerInLocalSpaceReturnsCorrectValues)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(-2.5f), Nrt_GeoBounds_getCornerInLocalSpace(bounds, 0)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(NrtGeoVector2F{+2.5f, -2.5f}, Nrt_GeoBounds_getCornerInLocalSpace(bounds, 1)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(+2.5f), Nrt_GeoBounds_getCornerInLocalSpace(bounds, 2)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(NrtGeoVector2F{-2.5f, +2.5f}, Nrt_GeoBounds_getCornerInLocalSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, getCornerInWorldSpaceReturnsCorrectValues)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_one(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(-1.5f), Nrt_GeoBounds_getCornerInWorldSpace(bounds, 0)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(NrtGeoVector2F{+3.5f, -1.5f}, Nrt_GeoBounds_getCornerInWorldSpace(bounds, 1)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(+3.5f), Nrt_GeoBounds_getCornerInWorldSpace(bounds, 2)));
    EXPECT_TRUE(Nrt_GeoVector2F_equal(NrtGeoVector2F{-1.5f, +3.5f}, Nrt_GeoBounds_getCornerInWorldSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, pointIsWithinBoundsReturnsTrueWhenWithinBounds)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_pointIsWithinBounds(bounds, Nrt_GeoVector2F_one()));
}

TEST(InteropGeoBoundsTest, pointIsWithinBoundsReturnsFalseWhenNotWithinBounds)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_pointIsWithinBounds(bounds, Nrt_GeoVector2F_uniform(10.0f)));
}

TEST(InteropGeoBoundsTest, getExtentsReturnsCorrectExtentsValue)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_one(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_equal(Nrt_GeoVector2F_uniform(2.5f), Nrt_GeoBounds_getExtents(bounds)));
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsTrueWhenIntersecting)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(1.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    ASSERT_EQ(Nrt_GeoBounds_intersectsWith(bounds0, bounds1, &output), NRT_SUCCESS);
    EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsTrueWhenIntersectingInversed)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(1.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    ASSERT_EQ(Nrt_GeoBounds_intersectsWith(bounds1, bounds0, &output), NRT_SUCCESS);
    EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersecting)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(100.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    int32_t output = NRT_TRUE;

    ASSERT_EQ(Nrt_GeoBounds_intersectsWith(bounds0, bounds1, &output), NRT_SUCCESS);
    EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersectingInversed)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(100.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    int32_t output = NRT_TRUE;

    ASSERT_EQ(Nrt_GeoBounds_intersectsWith(bounds1, bounds0, &output), NRT_SUCCESS);
    EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsErrorCodeWhenBoundsAreRotated)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 20.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(1.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    EXPECT_EQ(Nrt_GeoBounds_intersectsWith(bounds1, bounds0, &output), NRT_FAILURE_NOT_SUPPORTED);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsNullptrFailureWhenGivenNullptr)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_zero(), Nrt_GeoVector2F_uniform(5.0f), 20.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_uniform(1.0f), Nrt_GeoVector2F_uniform(5.0f), 0.0f};

    ASSERT_EQ(Nrt_GeoBounds_intersectsWith(bounds1, bounds0, nullptr), NRT_FAILURE_NULL_ARGUMENT_PROVIDED);
}
