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

