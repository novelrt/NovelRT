// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT.Interop/Maths/NrtGeoVector2F.h>
#include <NovelRT.Interop/Maths/NrtQuadTreePoint.h>
#include <NovelRT.Interop/NrtErrorHandling.h>
#include <NovelRT/NovelRT.h>

#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Maths;

TEST(InteropQuadTreePointTest, CreateReturnsValidHandle)
{
    NrtGeoVector2F vec = Nrt_GeoVector2F_One();
    EXPECT_NE(Nrt_QuadTreePoint_Create(vec), nullptr);
}

TEST(InteropQuadTreePointTest, CreateFromFloatReturnsValidHandle)
{
    EXPECT_NE(reinterpret_cast<Maths::QuadTreePoint*>(Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f)), nullptr);
}

TEST(InteropQuadTreePointTest, DeleteReturnsSuccess)
{
    EXPECT_EQ(Nrt_QuadTreePoint_Destroy(Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f)), NRT_SUCCESS);
}

TEST(InteropQuadTreePointTest, DeleteReturnsNullInstanceFailureWhenGivenNullptr)
{
    const char* outputError = "Unable to continue. A null instance was provided when an instance was expected.";
    ASSERT_EQ(Nrt_QuadTreePoint_Destroy(nullptr), NRT_FAILURE_NULL_INSTANCE_PROVIDED);
    EXPECT_STREQ(outputError, Nrt_getLastError());
}

TEST(InteropQuadTreePointTest,
     DeleteReturnsAlreadyDeletedOrRemovedWhenPointIsBeingHeldOntoElsewhereAndHasAlreadyBeenDeletedFromCache)
{
    const char* outputError = "Unable to continue. The specific item has already been deleted or removed.";
    auto ptr =
        reinterpret_cast<Maths::QuadTreePoint*>(Nrt_QuadTreePoint_CreateFromFloat(1.0f, 1.0f))->shared_from_this();
    ASSERT_EQ(Nrt_QuadTreePoint_Destroy(reinterpret_cast<NrtQuadTreePointHandle>(ptr.get())), NRT_SUCCESS);
    ASSERT_EQ(Nrt_QuadTreePoint_Destroy(reinterpret_cast<NrtQuadTreePointHandle>(ptr.get())),
              NRT_FAILURE_ALREADY_DELETED_OR_REMOVED);

    EXPECT_STREQ(outputError, Nrt_getLastError());
}
