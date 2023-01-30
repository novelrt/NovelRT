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
    NrtGeoBounds expectedBounds{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_Equal(expectedBounds, Nrt_GeoBounds_zero()));
}

TEST(InteropGeoBoundsTest, EqualsOperatorReturnsTrueWhenBoundsAreEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_Equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, EqualsOperatorReturnsFalseWhenBoundsAreNotEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(10.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_Equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, NotEqualsOperatorReturnsFalseWhenBoundsAreEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_NotEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, NotEqualsOperatorReturnsTrueWhenBoundsAreNotEqual)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(10.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Zero(), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_NotEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, GetCornerInLocalSpaceReturnsCorrectValues)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(-2.5f), Nrt_GeoBounds_GetCornerInLocalSpace(bounds, 0)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(NrtGeoVector2F{+2.5f, -2.5f}, Nrt_GeoBounds_GetCornerInLocalSpace(bounds, 1)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(+2.5f), Nrt_GeoBounds_GetCornerInLocalSpace(bounds, 2)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(NrtGeoVector2F{-2.5f, +2.5f}, Nrt_GeoBounds_GetCornerInLocalSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, GetCornerInWorldSpaceReturnsCorrectValues)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_One(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(-1.5f), Nrt_GeoBounds_GetCornerInWorldSpace(bounds, 0)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(NrtGeoVector2F{+3.5f, -1.5f}, Nrt_GeoBounds_GetCornerInWorldSpace(bounds, 1)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(+3.5f), Nrt_GeoBounds_GetCornerInWorldSpace(bounds, 2)));
    EXPECT_TRUE(Nrt_GeoVector2F_Equal(NrtGeoVector2F{-1.5f, +3.5f}, Nrt_GeoBounds_GetCornerInWorldSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, PointIsWithinBoundsReturnsTrueWhenWithinBounds)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoBounds_PointIsWithinBounds(bounds, Nrt_GeoVector2F_One()));
}

TEST(InteropGeoBoundsTest, PointIsWithinBoundsReturnsFalseWhenNotWithinBounds)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    EXPECT_FALSE(Nrt_GeoBounds_PointIsWithinBounds(bounds, Nrt_GeoVector2F_Uniform(10.0f)));
}

TEST(InteropGeoBoundsTest, GetExtentsReturnsCorrectExtentsValue)
{
    NrtGeoBounds bounds{Nrt_GeoVector2F_One(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    EXPECT_TRUE(Nrt_GeoVector2F_Equal(Nrt_GeoVector2F_Uniform(2.5f), Nrt_GeoBounds_GetExtents(bounds)));
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsTrueWhenIntersecting)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(1.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    ASSERT_EQ(Nrt_GeoBounds_IntersectsWith(bounds0, bounds1, &output), NRT_SUCCESS);
    EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsTrueWhenIntersectingInversed)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(1.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    ASSERT_EQ(Nrt_GeoBounds_IntersectsWith(bounds1, bounds0, &output), NRT_SUCCESS);
    EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsFalseWhenNotIntersecting)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(100.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    int32_t output = NRT_TRUE;

    ASSERT_EQ(Nrt_GeoBounds_IntersectsWith(bounds0, bounds1, &output), NRT_SUCCESS);
    EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsFalseWhenNotIntersectingInversed)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(100.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    int32_t output = NRT_TRUE;

    ASSERT_EQ(Nrt_GeoBounds_IntersectsWith(bounds1, bounds0, &output), NRT_SUCCESS);
    EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsErrorCodeWhenBoundsAreRotated)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 20.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(1.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};
    int32_t output = NRT_FALSE;

    EXPECT_EQ(Nrt_GeoBounds_IntersectsWith(bounds1, bounds0, &output), NRT_FAILURE_NOT_SUPPORTED);
}

TEST(InteropGeoBoundsTest, IntersectsWithReturnsNullptrFailureWhenGivenNullptr)
{
    NrtGeoBounds bounds0{Nrt_GeoVector2F_Zero(), Nrt_GeoVector2F_Uniform(5.0f), 20.0f};
    NrtGeoBounds bounds1{Nrt_GeoVector2F_Uniform(1.0f), Nrt_GeoVector2F_Uniform(5.0f), 0.0f};

    ASSERT_EQ(Nrt_GeoBounds_IntersectsWith(bounds1, bounds0, nullptr), NRT_FAILURE_NULL_ARGUMENT_PROVIDED);
}
