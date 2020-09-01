// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include <NovelRT.Interop/Maths/NovelRTGeoBounds.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropGeoBoundsTest, zeroReturnsZeroedOutGeoBounds) {
  NovelRTGeoBounds expectedBounds { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };

  EXPECT_TRUE(NovelRT_GeoBounds_equal(expectedBounds, NovelRT_GeoBounds_zero()));
}

TEST(InteropGeoBoundsTest, equalsOperatorReturnsTrueWhenBoundsAreEqual) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };

  EXPECT_TRUE(NovelRT_GeoBounds_equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, equalsOperatorReturnsFalseWhenBoundsAreNotEqual) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(10.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };

  EXPECT_FALSE(NovelRT_GeoBounds_equal(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, notEqualsOperatorReturnsFalseWhenBoundsAreEqual) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };

  EXPECT_FALSE(NovelRT_GeoBounds_notEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, notEqualsOperatorReturnsTrueWhenBoundsAreNotEqual) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(10.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_zero(), 0.0f };

  EXPECT_TRUE(NovelRT_GeoBounds_notEqual(bounds0, bounds1));
}

TEST(InteropGeoBoundsTest, getCornerInLocalSpaceReturnsCorrectValues) {
  NovelRTGeoBounds bounds { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };

  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(-2.5f), NovelRT_GeoBounds_getCornerInLocalSpace(bounds, 0)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRTGeoVector2F { +2.5f, -2.5f }, NovelRT_GeoBounds_getCornerInLocalSpace(bounds, 1)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(+2.5f), NovelRT_GeoBounds_getCornerInLocalSpace(bounds, 2)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRTGeoVector2F {-2.5f, +2.5f }, NovelRT_GeoBounds_getCornerInLocalSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, getCornerInWorldSpaceReturnsCorrectValues) {
  NovelRTGeoBounds bounds { NovelRT_GeoVector2F_one(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };

  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(-1.5f), NovelRT_GeoBounds_getCornerInWorldSpace(bounds, 0)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRTGeoVector2F { +3.5f, -1.5f }, NovelRT_GeoBounds_getCornerInWorldSpace(bounds, 1)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(+3.5f), NovelRT_GeoBounds_getCornerInWorldSpace(bounds, 2)));
  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRTGeoVector2F {-1.5f, +3.5f }, NovelRT_GeoBounds_getCornerInWorldSpace(bounds, 3)));
}

TEST(InteropGeoBoundsTest, pointIsWithinBoundsReturnsTrueWhenWithinBounds) {
  NovelRTGeoBounds bounds { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };

  EXPECT_TRUE(NovelRT_GeoBounds_pointIsWithinBounds(bounds, NovelRT_GeoVector2F_one()));
}

TEST(InteropGeoBoundsTest, pointIsWithinBoundsReturnsFalseWhenNotWithinBounds) {
  NovelRTGeoBounds bounds { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };

  EXPECT_FALSE(NovelRT_GeoBounds_pointIsWithinBounds(bounds, NovelRT_GeoVector2F_uniform(10.0f)));
}

TEST(InteropGeoBoundsTest, getExtentsReturnsCorrectExtentsValue) {
  NovelRTGeoBounds bounds { NovelRT_GeoVector2F_one(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };

  EXPECT_TRUE(NovelRT_GeoVector2F_equal(NovelRT_GeoVector2F_uniform(2.5f), NovelRT_GeoBounds_getExtents(bounds)));
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsTrueWhenIntersecting) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(1.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTBool output = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_GeoBounds_intersectsWith(bounds0, bounds1, &output, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsTrueWhenIntersectingInversed) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(1.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTBool output = NOVELRT_FALSE;

  ASSERT_EQ(NovelRT_GeoBounds_intersectsWith(bounds1, bounds0, &output, nullptr), NOVELRT_SUCCESS);
  EXPECT_TRUE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersecting) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(100.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTBool output = NOVELRT_TRUE;

  ASSERT_EQ(NovelRT_GeoBounds_intersectsWith(bounds0, bounds1, &output, nullptr), NOVELRT_SUCCESS);
  EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsFalseWhenNotIntersectingInversed) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(100.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTBool output = NOVELRT_TRUE;

  ASSERT_EQ(NovelRT_GeoBounds_intersectsWith(bounds1, bounds0, &output, nullptr), NOVELRT_SUCCESS);
  EXPECT_FALSE(output);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsErrorCodeWhenBoundsAreRotated) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 20.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(1.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  NovelRTBool output = NOVELRT_FALSE;

  EXPECT_EQ(NovelRT_GeoBounds_intersectsWith(bounds1, bounds0, &output, nullptr), NOVELRT_FAILURE);
}

TEST(InteropGeoBoundsTest, intersectsWithReturnsNullptrFailurWhenGivenNullptr) {
  NovelRTGeoBounds bounds0 { NovelRT_GeoVector2F_zero(), NovelRT_GeoVector2F_uniform(5.0f), 20.0f };
  NovelRTGeoBounds bounds1 { NovelRT_GeoVector2F_uniform(1.0f), NovelRT_GeoVector2F_uniform(5.0f), 0.0f };
  const char* errorMessage = nullptr;

  ASSERT_EQ(NovelRT_GeoBounds_intersectsWith(bounds1, bounds0, nullptr, &errorMessage), NOVELRT_FAILURE);
  EXPECT_EQ(errorMessage, NovelRT_getErrMsgIsNullptr());
}
