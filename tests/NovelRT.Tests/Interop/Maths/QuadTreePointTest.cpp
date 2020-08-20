// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTQuadTreePoint.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropQuadTreePointTest, QuadTreePoint_createReturnsValidHandle) {
  NovelRTGeoVector2F vec = NovelRT_GeoVector2F_one();
  EXPECT_NE(NovelRT_QuadTreePoint_create(vec), nullptr);
}

TEST(InteropQuadTreePointTest, QuadTreePoint_createFromFloatReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTreePoint*>(NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f)), nullptr);
}

TEST(InteropQuadTreePoint, QuadTreePoint_deleteReturnsSuccess) {
  EXPECT_EQ(NovelRT_QuadTreePoint_delete(NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f), nullptr), NOVELRT_SUCCESS);
}

