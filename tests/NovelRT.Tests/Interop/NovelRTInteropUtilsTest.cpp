// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <NovelRT.Interop/NovelRTInteropUtils.h>
#include <gtest/gtest.h>
#include <string>

TEST(InteropUtilsTest, translateErrorCodeTranslatesErrorCodeFromDefaultToCpuCode) {
    const char* ptr = NovelRT_translateErrorCode(NovelRT_getCpuLangKey(), NovelRT_getErrMsgIsNullptr());
    EXPECT_EQ(std::string("FAILURE_IS_NULLPTR"), std::string(ptr));
}