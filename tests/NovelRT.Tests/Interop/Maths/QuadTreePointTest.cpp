// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NovelRTQuadTreePoint.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropQuadTreePointTest, createReturnsValidHandle) {
  NovelRTGeoVector2F vec = NovelRT_GeoVector2F_one();
  EXPECT_NE(NovelRT_QuadTreePoint_create(vec), nullptr);
}

TEST(InteropQuadTreePointTest, createFromFloatReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTreePoint*>(NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f)), nullptr);
}

TEST(InteropQuadTreePointTest, deleteReturnsSuccess) {
  EXPECT_EQ(NovelRT_QuadTreePoint_delete(NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f), nullptr), NOVELRT_SUCCESS);
}

TEST(InteropQuadTreePointTest, deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* outputError = nullptr;
  ASSERT_EQ(NovelRT_QuadTreePoint_delete(nullptr, &outputError), NOVELRT_FAILURE);
  EXPECT_EQ(outputError, NovelRT_getErrMsgIsNullptr());
}

TEST(InteropQuadTreePointTest, deleteReturnsAlreadyDeletedOrRemovedWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache) {
  const char* outputError = nullptr;
  auto ptr = reinterpret_cast<Maths::QuadTreePoint*>(NovelRT_QuadTreePoint_createFromFloat(1.0f, 1.0f))->shared_from_this();
  ASSERT_EQ(NovelRT_QuadTreePoint_delete(reinterpret_cast<NovelRTQuadTreePoint>(ptr.get()), &outputError), NOVELRT_SUCCESS);
  ASSERT_EQ(NovelRT_QuadTreePoint_delete(reinterpret_cast<NovelRTQuadTreePoint>(ptr.get()), &outputError), NOVELRT_FAILURE);
  
  EXPECT_EQ(outputError, NovelRT_getErrMsgIsAlreadyDeletedOrRemoved());
}

