// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/QuadTreePoint_t.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

//TODO: ERROR. CODES.
TEST(InteropQuadTreePointTest, QuadTreePoint_createReturnsValidHandle) {
  auto vec = GeoVector2F_create(1.0f, 1.0f);
  auto point = reinterpret_cast<Maths::QuadTreePoint*>(QuadTreePoint_create(vec));
  EXPECT_NE(point, nullptr);
}

TEST(InteropQuadTreePoint, QuadTreePoint_deleteReturnsSuccess) {
  EXPECT_NO_THROW(QuadTreePoint_delete(QuadTreePoint_createFromFloat(1.0f, 1.0f)));
}

TEST(InteropQuadTreePointTest, QuadTreePoint_createFromFloatReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTreePoint*>(QuadTreePoint_createFromFloat(1.0f, 1.0f)), nullptr);
}