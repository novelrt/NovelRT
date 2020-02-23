// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root for more information.

#include <gtest/gtest.h>
#include <NovelRT.h>

using namespace NovelRT;
using namespace NovelRT::Utilities;

enum class TestEnum : uint32_t {
  a = 0,
  b = 1 << 0,
  c = 1 << 1,
  d = 1 << 2
};

TEST(BitflagsTest, bitwiseOr) {
  auto flags = TestEnum::b | TestEnum::c | TestEnum::d;
  EXPECT_TRUE((flags & TestEnum::b) == TestEnum::b);
  EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
  EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}
