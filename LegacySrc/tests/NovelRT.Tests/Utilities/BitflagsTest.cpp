// Copyright © Matt Jones and Contributors. Licensed under the MIT License (MIT). See LICENCE.md in the repository root
// for more information.

#include <NovelRT/NovelRT.h>
#include <gtest/gtest.h>

using namespace NovelRT;
using namespace NovelRT::Utilities;

enum class TestEnum : uint32_t
{
    a = 0,
    b = 1 << 0,
    c = 1 << 1,
    d = 1 << 2
};

TEST(BitflagsTest, bitwiseOr)
{
    auto flags = TestEnum::b | TestEnum::c | TestEnum::d;
    EXPECT_TRUE((flags & TestEnum::b) == TestEnum::b);
    EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
    EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}

TEST(BitflagsTest, bitwiseAnd)
{
    auto flags = (TestEnum::b | TestEnum::c) & (TestEnum::c | TestEnum::d);
    EXPECT_EQ(flags, TestEnum::c);
    EXPECT_NE(flags, TestEnum::b);
}

TEST(BitflagsTest, bitwiseComplement)
{
    auto flags = ~TestEnum::a;
    EXPECT_TRUE((flags & TestEnum::b) == TestEnum::b);
    EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
    EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}

TEST(BitflagsTest, bitwiseXor)
{
    auto allFlags = ~TestEnum::a;
    auto flags = TestEnum::b ^ allFlags;

    EXPECT_FALSE((flags & TestEnum::b) == TestEnum::b);
    EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
    EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}

TEST(BitflagsTest, bitwiseOrEquals)
{
    auto flags = TestEnum::b;
    flags |= TestEnum::c;
    flags |= TestEnum::d;

    EXPECT_TRUE((flags & TestEnum::b) == TestEnum::b);
    EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
    EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}

TEST(BitflagsTest, bitwiseAndEquals)
{
    auto flags = (TestEnum::b | TestEnum::c);
    flags &= (TestEnum::c | TestEnum::d);

    EXPECT_EQ(flags, TestEnum::c);
    EXPECT_NE(flags, TestEnum::b);
}

TEST(BitflagsTest, bitwiseXorEquals)
{
    auto flags = ~TestEnum::a;
    flags ^= TestEnum::b;

    EXPECT_FALSE((flags & TestEnum::b) == TestEnum::b);
    EXPECT_TRUE((flags & TestEnum::c) == TestEnum::c);
    EXPECT_TRUE((flags & TestEnum::d) == TestEnum::d);
}
