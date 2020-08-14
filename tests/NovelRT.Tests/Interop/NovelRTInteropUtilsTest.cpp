// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.Interop/NovelRTInteropUtils.h>
#include <gtest/gtest.h>

TEST(InteropUtilsTest, translateErrorCodeTranslatesErrorCodeFromDefaultToCpuCode) {
    const char* ptr = NovelRT_translateErrorCode("cpu", errMsgIsNullptr);
    EXPECT_EQ("FAILURE_IS_NULLPTR", ptr);
}