// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>
#include "NovelRT.Interop/Maths/NrtQuadTreePoint.h"

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropQuadTreePointTest, createReturnsValidHandle) {
  NrtGeoVector2F vec = Nrt_GeoVector2F_one();
  EXPECT_NE(Nrt_QuadTreePoint_create(vec), nullptr);
}

TEST(InteropQuadTreePointTest, createFromFloatReturnsValidHandle) {
  EXPECT_NE(reinterpret_cast<Maths::QuadTreePoint*>(Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f)), nullptr);
}

TEST(InteropQuadTreePointTest, deleteReturnsSuccess) {
  EXPECT_EQ(Nrt_QuadTreePoint_delete(Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f)), NRT_SUCCESS);
}

TEST(InteropQuadTreePointTest, deleteReturnsNullptrFailureWhenGivenNullptr) {
  const char* outputError = nullptr;
  ASSERT_EQ(Nrt_QuadTreePoint_delete(nullptr), NRT_FAILURE_UNKOWN);
  //EXPECT_EQ(outputError, Nrt_getErrMsgIsNullptr()); //TODO: fix this
}

TEST(InteropQuadTreePointTest, deleteReturnsAlreadyDeletedOrRemovedWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache) {
  const char* outputError = nullptr;
  auto ptr = reinterpret_cast<Maths::QuadTreePoint*>(Nrt_QuadTreePoint_createFromFloat(1.0f, 1.0f))->shared_from_this();
  ASSERT_EQ(Nrt_QuadTreePoint_delete(reinterpret_cast<NrtQuadTreePoint>(ptr.get())), NRT_SUCCESS);
  ASSERT_EQ(Nrt_QuadTreePoint_delete(reinterpret_cast<NrtQuadTreePoint>(ptr.get())), NRT_FAILURE_UNKOWN);
  
  //EXPECT_EQ(outputError, Nrt_getErrMsgIsAlreadyDeletedOrRemoved()); //TODO: fix this
}

